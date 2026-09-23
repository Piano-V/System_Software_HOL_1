#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "dup_test.txt";

    // Open file in write only mode (truncate if already exists)
    int fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Duplicate fd1 using dup()
    int fd2 = dup(fd1);

    printf("Original FD: %d, Duplicated FD (dup): %d\n", fd1, fd2);

    // Write through fd1
    const char *msg1 = "Written using original FD (fd1)\n";
    write(fd1, msg1, strlen(msg1));

    // Write through fd2
    const char *msg2 = "Written using duplicated FD (fd2)\n";
    write(fd2, msg2, strlen(msg2));

    close(fd1);
    close(fd2);

    printf("Check contents: cat %s\n", filename);
    return 0;
}

// ./q11a_dup
// cat dup_test.txt

// ./q11b_dup2
// cat dup2_test.txt

// ./q11c_fcntl
// cat fcntl_dup_test.txt