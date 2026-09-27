#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct record {
    int id;
    char name[32];
    int counter;
};

int main() {
    const char *filename = "records.db";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating records file");
        return 1;
    }

    struct record records[3] = {
        {1, "Record Alpha", 100},
        {2, "Record Beta",  200},
        {3, "Record Gamma", 300}
    };

    if (write(fd, records, sizeof(records)) != sizeof(records)) {
        perror("Error writing initial records");
        close(fd);
        return 1;
    }

    printf("Initialized records.db with 3 records.\n");

    close(fd);
    return 0;
}