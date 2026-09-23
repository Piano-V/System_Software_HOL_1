#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct record {
    int id;
    char name[32];
    int counter;
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <record_no: 1-3> <lock_type: r|w>\n", argv[0]);
        return 1;
    }

    int rec_no = atoi(argv[1]);
    char lock_choice = argv[2][0];

    if (rec_no < 1 || rec_no > 3) {
        fprintf(stderr, "Error: Record number must be 1, 2, or 3.\n");
        return 1;
    }

    if (lock_choice != 'r' && lock_choice != 'w') {
        fprintf(stderr, "Error: Lock type must be 'r' (read) or 'w' (write).\n");
        return 1;
    }

    const char *filename = "records.db";
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error opening records file (run ./q18_init_records first)");
        return 1;
    }

    off_t offset = (rec_no - 1) * sizeof(struct record);

    // Setup flock structure for the specific record
    struct flock lock;
    lock.l_type   = (lock_choice == 'w') ? F_WRLCK : F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start  = offset;
    lock.l_len    = sizeof(struct record); // Lock only this records byte length
    lock.l_pid    = getpid();

    printf("[PID %d] Requesting %s lock on Record %d (bytes %ld - %ld)...\n",
           getpid(), (lock_choice == 'w') ? "WRITE" : "READ", 
           rec_no, (long)offset, (long)(offset + sizeof(struct record) - 1));

    // F_SETLKW waits until the record is free
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl locking failed");
        close(fd);
        return 1;
    }

    printf("[PID %d] %s lock ACQUIRED on Record %d.\n",
           getpid(), (lock_choice == 'w') ? "WRITE" : "READ", rec_no);

    // Seek to the target record
    lseek(fd, offset, SEEK_SET);
    struct record rec;
    read(fd, &rec, sizeof(struct record));

    printf("[PID %d] Current data: [ID: %d | Name: %s | Counter: %d]\n",
           getpid(), rec.id, rec.name, rec.counter);

    if (lock_choice == 'w') {
        rec.counter += 10;
        printf("[PID %d] Updating counter to %d...\n", getpid(), rec.counter);
        
        // Write the updated record back to its slot
        lseek(fd, offset, SEEK_SET);
        write(fd, &rec, sizeof(struct record));
    }

    printf("[PID %d] Holding lock for 7 seconds to demonstrate locking...\n", getpid());
    sleep(7);

    // Release the record lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("[PID %d] Lock RELEASED on Record %d. Done.\n\n", getpid(), rec_no);

    close(fd);
    return 0;
}