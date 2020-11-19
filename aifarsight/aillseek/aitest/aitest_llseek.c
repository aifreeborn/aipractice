#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = -1;
	char *start;
	int i;
	char buf[32];

	fd = open("/dev/aillseek", O_RDWR);
	if (fd < 0) {
		perror("open failed!");
		return EXIT_FAILURE;
	}
	
	start = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (start == MAP_FAILED) {
		perror("mmap failed!");
		close(fd);
		return EXIT_FAILURE;
	}

	for (i = 0; i < 26; i++) {
		*(start + i) = 'a' + i; 
	}
	*(start + i) = '\0';

	if (-1 == lseek(fd, 3, SEEK_SET)) {
		perror("lseek failed!");
		close(fd);
		munmap(start, 32);
		return EXIT_FAILURE;
	}

	if (-1 == read(fd, buf, 10)) {
		perror("read failed");
		close(fd);
		munmap(start, 32);
		return EXIT_FAILURE;
	}

	buf[10] = '\0';
	puts(buf);

	close(fd);
	munmap(start, 32);
	return EXIT_SUCCESS;
}
