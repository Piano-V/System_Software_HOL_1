#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("locked_file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Requesting write lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl write lock failed");
        close(fd);
        return 1;
    }

    printf("Write lock acquired. Holding lock for 15 seconds...\n");
    dprintf(fd, "Write lock held by PID %d\n", getpid());
    sleep(15);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released.\n");

    close(fd);
    return 0;
}
