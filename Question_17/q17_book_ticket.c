#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct ticket_data {
    int ticket_no;
};

int main() {
    int fd = open("ticket.db", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct ticket_data);

    printf("Waiting to acquire lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl lock failed");
        close(fd);
        return 1;
    }

    printf("Lock acquired.\n");

    struct ticket_data data;
    lseek(fd, 0, SEEK_SET);
    read(fd, &data, sizeof(data));

    printf("Current ticket number: %d\n", data.ticket_no);
    int booked = data.ticket_no;
    data.ticket_no++;

    lseek(fd, 0, SEEK_SET);
    write(fd, &data, sizeof(data));

    printf("Booked ticket: %d\n", booked);
    printf("Holding lock for 5 seconds...\n");
    sleep(5);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released.\n");

    close(fd);
    return 0;
}