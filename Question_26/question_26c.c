#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *envp[] = { "PATH=/bin:/usr/bin", NULL };

    printf("Executing ls -Rl using execle...\n");
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, envp);
    perror("execle failed");
    return 1;
}
