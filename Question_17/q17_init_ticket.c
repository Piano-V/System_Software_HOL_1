#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct ticket_data {
    int ticket_no;
};

int main() {
    const char *db_file = "ticket.db";

    int fd = open(db_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating ticket database");
        return 1;
    }

    struct ticket_data data;
    data.ticket_no = 1;

    if (write(fd, &data, sizeof(data)) != sizeof(data)) {
        perror("Error writing initial ticket number");
        close(fd);
        return 1;
    }

    printf("Ticket database initialized in '%s' with starting Ticket No: %d\n", db_file, data.ticket_no);

    close(fd);
    return 0;
}