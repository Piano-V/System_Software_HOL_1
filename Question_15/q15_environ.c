#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main() {
    int count = 0;

    for (char **env = environ; *env != NULL; env++) {
        printf("%d: %s\n", ++count, *env);
    }

    printf("\nTotal variables: %d\n", count);
    return 0;
}