#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "aivserial.h"

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	unsigned int baud;
	struct aivserial_option opt = {8, 1, 1};

	fd = open("/dev/aivserial", O_RDWR);
	if (fd < 0) {
		perror("open failed!");
		return EXIT_FAILURE;
	}

	baud = 9600;
	ret = ioctl(fd, AI_VSERIAL_SET_BAUD, baud);
	if (ret < 0)
		goto ioctl_err;

	ret = ioctl(fd, AI_VSERIAL_GET_BAUD, baud);
	if (ret < 0)
		goto ioctl_err;

	ret = ioctl(fd, AI_VSERIAL_SET_FFMT, &opt);
	if (ret < 0)
		goto ioctl_err;

	ret = ioctl(fd, AI_VSERIAL_GET_FFMT, &opt);
	if (ret < 0)
		goto ioctl_err;

	printf("baud rate: %d\n", baud);
	printf("frame format: %d%c%d\n", opt.datab, opt.parity == 0 ? 'N' :
			opt.parity == 1 ? 'O' : 'E',
			opt.stopb);
	close(fd);
	return EXIT_SUCCESS;

ioctl_err:
	perror("ioctl failed!");
	close(fd);
	return EXIT_FAILURE;
}
