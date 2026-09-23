#include <stdio.h>
#include <unistd.h>

int main() {
    const char *target = "target.txt";
    const char *linkpath = "c_hardlink.txt";

    if (link(target, linkpath) == -1) {
        perror("Error creating hard link");
        return 1;
    }

    printf("Hard link created successfully: %s linked to %s\n", linkpath, target);
    return 0;
}