################################################################################
# Name       : Makefile
# Author     : Didier Barvaux <didier.barvaux@toulouse.viveris.com>
# Description: create the libsignalfd tests
################################################################################


TESTS = \
	test_signalfd

check_PROGRAMS = \
	test_signalfd


test_signalfd_SOURCES = \
	test_signalfd.c
test_signalfd_CFLAGS = \
	$(configure_cflags)
test_signalfd_CPPFLAGS = \
	-I$(top_srcdir)/src/include
test_signalfd_LDADD = \
	-lsignalfd
test_signalfd_LDFLAGS = \
	$(configure_ldflags) \
	-L$(top_builddir)/src/.libs

