#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Inode: %ld\n", (long)st.st_ino);
    printf("Hard links: %ld\n", (long)st.st_nlink);
    printf("UID: %d\n", st.st_uid);
    printf("GID: %d\n", st.st_gid);
    printf("Size: %ld bytes\n", (long)st.st_size);
    printf("Block size: %ld bytes\n", (long)st.st_blksize);
    printf("Blocks: %lld\n", (long long)st.st_blocks);
    printf("Last access: %s", ctime(&st.st_atime));
    printf("Last modification: %s", ctime(&st.st_mtime));
    printf("Last change: %s", ctime(&st.st_ctime));

    return 0;
}