#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No arguments received.\n");
        return 1;
    }

    printf("Running inside target executable!\n");
    printf("Hello, %s!\n", argv[1]);
    printf("Total arguments received: %d\n", argc);

    return 0;
}
