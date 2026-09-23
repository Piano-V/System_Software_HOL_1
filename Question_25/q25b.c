#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("[Process PID: %d] Running executable program...\n", getpid());

    // Validate that input argument is passed
    if (argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        printf("Example: %s John\n", argv[0]);
        return 1;
    }

    // Access and process input passed to the executable
    printf("Hello, %s! Welcome to Systems Programming.\n", argv[1]);
    printf("Received argument: '%s' (Total arguments argc: %d)\n", argv[1], argc);

    return 0;
}

/*
Compilation:
gcc question_25b.c -o a.out

Execution:
./a.out Abhinav

Sample Output:
[Process PID: 5490] Running executable program...
Hello, Abhinav! Welcome to Systems Programming.
Received argument: 'Abhinav' (Total arguments argc: 2)
*/