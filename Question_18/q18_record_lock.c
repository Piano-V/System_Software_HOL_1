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
        printf("Usage: %s <record_no: 1-3> <lock_type: r|w>\n", argv[0]);
        return 1;
    }

    int rec_no = atoi(argv[1]);
    char lock_choice = argv[2][0];

    if (rec_no < 1 || rec_no > 3) {
        printf("Record number must be 1, 2, or 3.\n");
        return 1;
    }

    int fd = open("records.db", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    off_t offset = (rec_no - 1) * sizeof(struct record);

    struct flock lock;
    lock.l_type   = (lock_choice == 'w') ? F_WRLCK : F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start  = offset;
    lock.l_len    = sizeof(struct record);

    printf("Requesting %s lock on Record %d...\n", (lock_choice == 'w') ? "write" : "read", rec_no);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl lock failed");
        close(fd);
        return 1;
    }

    printf("Lock acquired on Record %d\n", rec_no);

    lseek(fd, offset, SEEK_SET);
    struct record rec;
    read(fd, &rec, sizeof(struct record));

    printf("Current: ID=%d, Name=%s, Counter=%d\n", rec.id, rec.name, rec.counter);

    if (lock_choice == 'w') {
        rec.counter += 10;
        printf("Updated Counter to: %d\n", rec.counter);
        lseek(fd, offset, SEEK_SET);
        write(fd, &rec, sizeof(struct record));
    }

    printf("Holding lock for 7 seconds...\n");
    sleep(7);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released on Record %d\n", rec_no);

    close(fd);
    return 0;
}