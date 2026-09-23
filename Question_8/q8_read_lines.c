#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sample_lines.txt", O_RDONLY);
    if (fd < 0) return 1;

    char line[1024];
    char c;
    int i = 0;

    // Read byte into a buffer until a newline forms a line
    while (read(fd, &c, 1) > 0) {
        line[i++] = c;
        if (c == '\n') {
            write(1, line, i);
            i = 0;
        }
    }

    // write any leftover text at EOF that didnt end with '\n'
    if (i > 0) {
        write(1, line, i);
    }

    close(fd);
    return 0;
}