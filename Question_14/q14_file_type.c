#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void identify_file_type(const char *path) {
    struct stat file_stat;

    if (lstat(path, &file_stat) == -1) {
        perror("lstat failed");
        return;
    }

    mode_t mode = file_stat.st_mode;

    printf("Path: %s -> File Type: ", path);

    if (S_ISREG(mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO / Named Pipe\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown File Type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        identify_file_type(argv[i]);
    }

    return 0;
}