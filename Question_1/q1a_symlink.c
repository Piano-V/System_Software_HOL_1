#include <stdio.h>
#include <unistd.h>

int main() {
    const char *target = "target.txt";
    const char *linkpath = "c_softlink.txt";

    if (symlink(target, linkpath) == -1) {
        perror("Error creating symlink");
        return 1;
    }

    printf("Soft link created successfully: %s -> %s\n", linkpath, target);
    return 0;
}