#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main () {

	int fd = open("test.txt", O_WRONLY);
	if (fd == -1 ) {
		perror("Open: ");
		return 1;
	}
	int flags = fcntl(fd, F_GETFL);
	printf("Flag: %d\n", flags);
	printf("AccMode: %d\n", O_ACCMODE);
	printf("Access: %d\n", flags & O_ACCMODE);

	printf("%d, %d, %d \n", O_RDONLY, O_WRONLY, O_RDWR);
	return 1;
}