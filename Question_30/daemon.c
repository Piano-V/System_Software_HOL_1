#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (fork() > 0) {
        exit(0);
    }

    setsid();
    chdir("/");

    close(0);
    close(1);
    close(2);

    sleep(10);
    system("echo 'Task executed at: ' $(date) >> /tmp/task.log");

    return 0;
}