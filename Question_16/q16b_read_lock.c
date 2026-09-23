#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "locked_file.txt";

    // Read locks only require read access
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file (make sure locked_file.txt exists)");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;    // Shared read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;           // Entire file
    lock.l_pid = getpid();

    printf("[Process %d] Requesting READ lock on '%s'...\n", getpid(), filename);

    // F_SETLKW blocks if an exclusive write lock is already active
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl failed to acquire read lock");
        close(fd);
        return 1;
    }

    printf("[Process %d] READ lock ACQUIRED!\n", getpid());
    printf("Reading and holding lock for 10 seconds...\n");
    sleep(10);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("[Process %d] Lock RELEASED. Exiting.\n", getpid());

    close(fd);
    return 0;
}