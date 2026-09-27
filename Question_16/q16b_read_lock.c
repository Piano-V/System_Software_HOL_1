#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("locked_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Requesting read lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl read lock failed");
        close(fd);
        return 1;
    }

    printf("Read lock acquired. Reading and holding lock for 10 seconds...\n");
    sleep(10);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released.\n");

    close(fd);
    return 0;
}