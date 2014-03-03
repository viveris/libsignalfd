/*
 * Copyright (c) 2013-2014, Viveris Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   test_signalfd.c
 * @brief  Test the signalfd syscall
 * @author Didier Barvaux <didier.barvaux@toulouse.viveris.com>
 */

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

