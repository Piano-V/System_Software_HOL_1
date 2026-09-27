#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    int access_mode = flags & O_ACCMODE;

    if (access_mode == O_RDONLY) printf("Mode: Read Only\n");
    else if (access_mode == O_WRONLY) printf("Mode: Write Only\n");
    else if (access_mode == O_RDWR) printf("Mode: Read/Write\n");

    close(fd);
    return 0;
}
