#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "locked_file.txt";

    // Open file in Read Write Mode
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;    // Exclusive write lock
    lock.l_whence = SEEK_SET; // From start of file
    lock.l_start = 0;         // Starting at byte 0
    lock.l_len = 0;           // 0 = Lock the entire file (all current and future bytes)
    lock.l_pid = getpid();

    printf("[Process %d] Requesting WRITE lock on '%s' \n", getpid(), filename);

    // F_SETLKW waits until the lock is acquired
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl fail");
        close(fd);
        return 1;
    }

    printf("[Process %d] WRITE lock ACQUIRED!\n", getpid());
    printf("Writing to file and holding lock for 15 seconds.\n");

    dprintf(fd, "Write lock held by PID %d\n", getpid());
    sleep(15);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("[Process %d] Lock RELEASED. Exiting.\n", getpid());

    close(fd);
    return 0;
}
