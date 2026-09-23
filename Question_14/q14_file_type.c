#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void identify_file_type(const char *path) {
    struct stat file_stat;

    // Use lstat() so we can inspect symbolic links without following them
    if (lstat(path, &file_stat) == -1) {
        perror("lstat failed");
        return;
    }

    mode_t mode = file_stat.st_mode;

    printf("Path: %-25s -> File Type: ", path);

    if (S_ISREG(mode)) {
        printf("Regular File (-)\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory (d)\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link (l)\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO / Named Pipe (p)\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device (c)\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device (b)\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket (s)\n");
    } else {
        printf("Unknown File Type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        identify_file_type(argv[i]);
    }

    return 0;
}

/*
pianov@Piano:~/hands-on/14$ ./q14_file_type sample_reg.txt sample_dir sample_link sample_fifo /dev/null /dev/sda
Path: sample_reg.txt            -> File Type: Regular File (-)
Path: sample_dir                -> File Type: Directory (d)
Path: sample_link               -> File Type: Symbolic Link (l)
Path: sample_fifo               -> File Type: FIFO / Named Pipe (p)
Path: /dev/null                 -> File Type: Character Device (c)
Path: /dev/sda                  -> File Type: Block Device (b)
*/