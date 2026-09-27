#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Starting launcher process (PID: %d)...\n", getpid());
    printf("execl called with argument: %s\n", argv[1]);

    execl("./q25_target", "q25_target", argv[1], (char *)NULL);

    perror("execl failed");
    return 1;
}
