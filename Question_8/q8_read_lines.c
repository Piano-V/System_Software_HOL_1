#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sample_lines.txt", O_RDONLY);
    if (fd < 0) return 1;

    char line[1024];
    char c;
    int i = 0;

    // reading byte into a buffer until a newline
    while (read(fd, &c, 1) > 0) {
        line[i++] = c;
        if (c == '\n') {
            write(1, line, i);
            i = 0;
        }
    }

    if (i > 0) {
        write(1, line, i);
    }

    close(fd);
    return 0;
}