#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Executing ls -l using execl...\n");
    execl("/bin/ls", "ls", "-l", (char *)NULL);
    perror("execl failed");
    return 1;
}