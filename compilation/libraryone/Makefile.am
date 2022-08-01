lib_LTLIBRARIES = libhello.la
libhello_la_SOURCES = $(top_srcdir)/source/hello/hello.cc $(top_srcdir)/include/libraryone/hello/hello.h
hellodir = $(includedir)/libraryone/hello
hello_HEADERS = include/libraryone/hello/hello.h

lib_LTLIBRARIES += libhelloint.la
libhelloint_la_SOURCES = $(top_srcdir)/source/helloint/hello.cc $(top_srcdir)/include/libraryone/helloint/hello.h
hellointdir = $(includedir)/libraryone/helloint
helloint_HEADERS = include/libraryone/helloint/hello.h

basedir = $(includedir)/libraryone/base
base_HEADERS = include/libraryone/base/config.h

# Declare the next example program: this depends on the library we compile above.
examplesdir = $(bindir)/examples/libraryone/
examples_PROGRAMS = libraryone
libraryone_SOURCES = $(top_srcdir)/examples/libraryone/libraryone.cc
libraryone_LDADD = libhello.la libhelloint.la

# We have to include the build directory include folder as well since that contains config.h.
AM_CXXFLAGS=-I$(top_srcdir)/include -I$(top_builddir)/include

# Unlike step-4, zlib may not be available: in this case, however, these shell
# variables are undefined and will expand to nothing, so we can keep these two
# lines unchanged.
libhelloint_la_CPPFLAGS = $(ZLIB_CFLAGS)
libhelloint_la_LDFLAGS = $(ZLIB_LIBS)
