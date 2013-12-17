################################################################################
# Name       : Makefile
# Authors    : Didier Barvaux <didier.barvaux@toulouse.viveris.com>
# Description: create the libsignalfd library
################################################################################

lib_LTLIBRARIES = libsignalfd.la

libsignalfd_la_SOURCES = \
	signalfd.c

libsignalfd_la_LIBADD =

libsignalfd_la_LDFLAGS = \
	$(configure_ldflags) \
	-no-undefined \
	-version-info 0:0:0

libsignalfd_la_CFLAGS = \
	$(configure_cflags)

libsignalfd_la_CPPFLAGS =

sysheadersdir = $(includedir)/sys
sysheaders_HEADERS = include/sys/signalfd.h

bitsheadersdir = $(includedir)/bits
bitsheaders_HEADERS = include/bits/signalfd.h

noinst_HEADERS = syscall.h

