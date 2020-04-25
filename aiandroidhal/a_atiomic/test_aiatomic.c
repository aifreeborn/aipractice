#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int fd = -1;

	fd = open("/dev/atomic", 0);
	printf("handler: %d\n", fd);

	if (fd > 0) {
		getchar();
		close(fd);
	} else {
		printf("errno: %d\n", errno);
	}
	
	return 0;
}
