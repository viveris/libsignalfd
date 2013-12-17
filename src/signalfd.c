
#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "syscall.h"

int signalfd(int fd, const sigset_t *mask, int flags)
{
	return syscall(SYS_signalfd4, fd, mask, sizeof(mask), flags);
}

