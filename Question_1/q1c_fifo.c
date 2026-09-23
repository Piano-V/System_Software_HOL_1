#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_mknod = "c_myfifo1";

    // mknod() system call with S_IFIFO flag
    if (mknod(fifo_mknod, S_IFIFO | 0666, 0) == -1) {
        perror("Error with mknod");
    } else {
        printf("FIFO created by mknod(): %s\n", fifo_mknod);
    }

    return 0;
}