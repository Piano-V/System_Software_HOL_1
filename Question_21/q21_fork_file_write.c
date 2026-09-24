#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    const char *filename = "shared_output.txt";

    // O_TRUNC clears any previous runs and O_CREAT creates it if missing
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("File '%s' opened with FD %d before fork()\n", filename, fd);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        close(fd);
        return 1;
    } else if (pid == 0) {
        // Child process
        const char child_msg[] = "Line 1 written by child process\n"
                                "Line 2 written by child process\n";
        
        write(fd, child_msg, strlen(child_msg));
        printf("Child (PID %d) finished writing.\n", getpid());

        // Close childs reference to the file descriptor
        close(fd);
        exit(0);
    } else {
        // Parent Process
        const char parent_msg[] = "[PARENT] Line 1 written by parent process\n"
                                  "[PARENT] Line 2 written by parent process\n";

        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent (PID %d) finished writing\n", getpid());

        wait(NULL);
        close(fd);
    }

    return 0;
}