#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int fd;
	char *start;
	int i;
	char buf[32];

	fd = open("/dev/aillseek", O_RDWR);
	if (fd < 0) {
		perror("open /dev/aillseek fail");
		return EXIT_FAILURE;
	}

	start = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (start == MAP_FAILED) {
		perror("mmap failed");
		close(fd);
		return EXIT_FAILURE;
	}

	for (i = 0; i < 26; i++)
		*(start + i) = 'a' + i;
	*(start + i) = '\0';
	
	if (-1 == read(fd, buf, 27)) {
		perror("read failed");
		close(fd);
		munmap(start, 32);
		return EXIT_FAILURE;
	}

	puts(buf);
	munmap(start, 32);
	return EXIT_SUCCESS;
}
