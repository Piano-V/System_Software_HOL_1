#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    struct stat file_stat;

    // Retrieve file status
    if (stat(filepath, &file_stat) == -1) {
        perror("Error retrieving file statistics");
        return 1;
    }

    printf("\n");
    printf(" File Metadata: %s\n", filepath);
    printf("\n");

    // a. Inode
    printf("a. Inode Number:             %lu\n", (unsigned long)file_stat.st_ino);

    // b. Number of hard links
    printf("b. Number of Hard Links:      %lu\n", (unsigned long)file_stat.st_nlink);

    // c. UID
    printf("c. Owner UID:                 %u\n", file_stat.st_uid);

    // d. GID
    printf("d. Group GID:                 %u\n", file_stat.st_gid);

    // e. Size
    printf("e. Total Size (bytes):        %ld\n", (long)file_stat.st_size);

    // f. Block size
    printf("f. Preferred I/O Block Size:  %ld bytes\n", (long)file_stat.st_blksize);

    // g. Number of blocks
    printf("g. Blocks Allocated (512B):   %lld\n", (long long)file_stat.st_blocks);

    // h. Time of last access
    printf("h. Last Access Time (atime):  %s", ctime(&file_stat.st_atime));

    // i. Time of last modification
    printf("i. Last Modification (mtime): %s", ctime(&file_stat.st_mtime));

    // j. Time of last status change
    printf("j. Last Status Change (ctime):%s", ctime(&file_stat.st_ctime));

    printf("\n");

    return 0;
}