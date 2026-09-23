#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Fork and exit parent
    if (fork() > 0) {
        exit(0);
    }
    
    // Detach from terminal session
    setsid();
    
    // Change directory to root
    chdir("/");
    
    // Close standard file descriptors so terminal doesnt hang
    close(0);
    close(1);
    close(2);
    
    sleep(10);
    system("echo 'Task executed at: ' $(date) >> /tmp/task.log");

    return 0;
}
// cat /tmp/task.log