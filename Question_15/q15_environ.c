#include <stdio.h>
#include <unistd.h>

// Declare the external environment array pointer
extern char **environ;

int main() {
    int count = 0;

    printf("\n");
    printf("        User Process Environment Variables          \n");
    printf("\n");

    // Iterate through the array of pointers until reaching NULL
    for (char **env = environ; *env != NULL; env++) {
        printf("[%3d] %s\n", ++count, *env);
    }

    printf("\n");
    printf("Total environment variables found: %d\n", count);
    printf("\n");

    return 0;
}