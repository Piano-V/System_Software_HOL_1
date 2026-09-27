#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "existing_test.txt";

    // 1. Open existing file in Read-Write mode
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("Error opening with O_RDWR");
    } else {
        printf("Opened with O_RDWR successfully. FD = %d\n", fd);
        close(fd);
    }

    // 2. Try opening with O_EXCL (used with O_CREAT to ensure exclusive creation)
    int fd_excl = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd_excl < 0) {
        perror("O_CREAT | O_EXCL failed (as expected, file already exists)");
    } else {
        printf("Opened with O_EXCL. FD = %d\n", fd_excl);
        close(fd_excl);
    }

    return 0;
}
