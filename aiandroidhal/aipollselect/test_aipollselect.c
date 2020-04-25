#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 20


int main(int argc, const char *argv[])
{	
	int fd = -1, num = 0;
	fd_set rfds, wfds;
	char buf[BUFFER_SIZE] = {0};

	memset(buf, 0, BUFFER_SIZE);

	fd = open("/dev/ai_poll_select", O_RDWR | O_NONBLOCK);
	if (fd != -1) {
		while (1) {
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);

			FD_SET(fd, &rfds);
			FD_SET(fd, &wfds);

			select(fd + 1, &rfds, &wfds, NULL, NULL);
			if (FD_ISSET(fd, &rfds)) {
				printf("Data can be read!\n");
				read(fd, buf, BUFFER_SIZE);
				printf("value: %s\n", buf);
				memset(buf, 0, BUFFER_SIZE);
			}

			if (FD_ISSET(fd, &wfds)) {
				printf("Data can be wirtten\n");
			}

			sleep(1);
		}
	} else {
		printf("Device open failure\n");
	}

	return 0;
}
