#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *filename = "existing_test.txt";

    // Ensure the file exists for testing
    int setup_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (setup_fd != -1) {
        write(setup_fd, "Sample content for testing hi\n", 27);
        close(setup_fd);
        printf("Created '%s' for testing.\n\n", filename);
    }

    // Open an existing file in Read write (O_RDWR) mode
    printf("Opening '%s' with O_RDWR \n", filename);
    int fd1 = open(filename, O_RDWR);
    if (fd1 == -1) {
        perror("Failed to open with O_RDWR");
    } else {
        printf("Opened with O_RDWR. File Descriptor = %d\n\n", fd1);
        close(fd1);
    }

    // Experimenting with O_EXCL (used with O_CREAT)
    printf("Opening existing '%s' with O_RDWR | O_CREAT | O_EXCL \n", filename);
    int fd2 = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd2 == -1) {
        // Expected failure because file already exists
        perror("Result");
        printf("Error Code (errno = %d): %s\n", errno, strerror(errno));
        printf("O_CREAT | O_EXCL ensures exclusive creation. Since the file already exists, it fails safely.\n\n");
    } else {
        printf("File Descriptor = %d\n", fd2);
        close(fd2);
    }

    // What happens if O_EXCL is used WITHOUT O_CREAT?
    printf("Opening existing '%s' with O_RDWR | O_EXCL (No O_CREAT) \n", filename);
    int fd3 = open(filename, O_RDWR | O_EXCL);
    if (fd3 == -1) {
        perror("Result");
    } else {
        printf("Opened successfully. File Descriptor = %d\n", fd3);
        printf("O_EXCL has no effect on regular files unless O_CREAT is also specified \n");
        close(fd3);
    }

    return 0;
}