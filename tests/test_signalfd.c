
#include "sys/signalfd.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
	sigset_t mask;
	int fd;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);

	/* block signals */
	assert(sigprocmask(SIG_BLOCK, &mask, NULL) == 0);

	/* create */
	fd = signalfd(-1, &mask, 0);
	if(fd < 0)
	{
		fprintf(stderr, "signalfd() failed: %s (%d)\n", strerror(errno), errno);
		goto error;
	}

	/* update */
	sigaddset(&mask, SIGQUIT);
	assert(signalfd(fd, &mask, 0) == fd);

	/* error */
	assert(signalfd(fd + 1, &mask, 0) < 0 && errno == EBADF);
	assert(signalfd(0, &mask, 0) < 0 && errno == EINVAL);
	assert(signalfd(fd, &mask, ~(SFD_NONBLOCK|SFD_CLOEXEC)) < 0 && errno == EINVAL);

	return 0;

error:
	return 1;
}

