#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct ticket_data {
    int ticket_no;
};

int main() {
    const char *db_file = "ticket.db";

    int fd = open(db_file, O_RDWR);
    if (fd == -1) {
        perror("Error opening ticket database");
        return 1;
    }

    // Set up exclusive write lock structure
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct ticket_data);
    lock.l_pid = getpid();

    printf("[PID %d] Requesting write lock to book a ticket...\n", getpid());

    // F_SETLKW blocks until any existing lock is released
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire lock");
        close(fd);
        return 1;
    }

    printf("[PID %d] Write lock acquired! Entering critical section.\n", getpid());

    struct ticket_data data;

    // Read current ticket number
    lseek(fd, 0, SEEK_SET);
    if (read(fd, &data, sizeof(data)) != sizeof(data)) {
        perror("Error reading ticket data");
        close(fd);
        return 1;
    }

    printf("[PID %d] Current ticket number in file: %d\n", getpid(), data.ticket_no);
    
    int booked_ticket = data.ticket_no;
    data.ticket_no++; // Increment for next reservation

    // Rewind file pointer to beginning and write updated number back
    lseek(fd, 0, SEEK_SET);
    if (write(fd, &data, sizeof(data)) != sizeof(data)) {
        perror("Error writing updated ticket data");
        close(fd);
        return 1;
    }

    // Optional delay to simulate processing work and allow manual race testing
    printf("[PID %d] Processing transaction (holding lock for 5 seconds)...\n", getpid());
    sleep(5);

    printf("[PID %d] Ticket successfully booked: #%d\n", getpid(), booked_ticket);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("[PID %d] Lock released. Critical section closed.\n\n", getpid());

    close(fd);
    return 0;
}