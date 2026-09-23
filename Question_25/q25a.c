#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[Process PID: %d] Executing '/bin/ls -l' using execl() system call...\n\n", getpid());
    fflush(stdout);

    // execl replaces the current process image with the specified executable
    // Syntax: execl(path, arg0, arg1, ..., NULL)
    execl("/bin/ls", "ls", "-l", (char *)NULL);

    // This line will only be reached if execl() encounters an error
    perror("execl failed");
    return 1;
}

/*
gcc question_25a.c -o q25a

Execution:
./q25a

Sample Output:
[Process PID: 5432] Executing '/bin/ls -l' using execl() system call...

total 160
-rw-r--r-- 1 user user 1332 Sep 22 14:19 question_10.c
-rw-r--r-- 1 user user 1025 Sep 22 14:19 question_11a.c
*/