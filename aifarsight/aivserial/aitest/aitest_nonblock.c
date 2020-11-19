#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "aivserial.h"

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	char rbuf[32] = {0};
	char wbuf[32] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

	fd = open("/dev/aivserial", O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		perror("open failed!");
		return EXIT_FAILURE;
	}

	ret = read(fd, rbuf, sizeof(rbuf));
	if (ret < 0)
		perror("read");

	ret = write(fd, wbuf, sizeof(wbuf));
	if (ret < 0)
		perror("first write");

	ret = write(fd, wbuf, sizeof(wbuf));
	if (ret < 0)
		perror("second write");

	close(fd);
	return EXIT_SUCCESS;
}
