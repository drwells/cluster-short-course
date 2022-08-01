AC_INIT([libraryone], [0.9])
AC_PREREQ([2.69])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.9 foreign -Wall -Werror subdir-objects])
AM_PROG_AR
LT_INIT([])
AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CXXCPP

dnl Setup ZLIB
LIBRARYONE_ENABLE_ZLIB=no
ZLIB_ARGUMENT_MESSAGE=
AC_ARG_ENABLE(zlib,
              AS_HELP_STRING([--enable-zlib],
                             [Enable compression with zlib]),
              AS_CASE([$enableval],
                       [yes], [LIBRARYONE_ENABLE_ZLIB=yes],
                       [no],  [LIBRARYONE_ENABLE_ZLIB=no],
                       [*],   [AC_MSG_ERROR(Please use either --enable-zlib=yes or --enable-zlib=no; the value '$enableval' was not understood)]),
              [LIBRARYONE_ENABLE_ZLIB=yes])

if test "$LIBRARYONE_ENABLE_ZLIB" = "yes"; then
    AC_CHECK_HEADER(zlib.h, [LIBRARYONE_HAVE_ZLIB_H=yes])
    if test "$LIBRARYONE_HAVE_ZLIB_H" = "yes"; then
        AC_MSG_RESULT(Found zlib.h)
    else
        AC_MSG_ERROR(zlib.h not available!)
    fi

    _old_libs=$LIBS
    LIBS=""
    AC_CHECK_LIB(z, compress2)
    if test "$LIBS" != ""; then
        AC_MSG_RESULT(Found libz)
    else
        AC_MSG_ERROR(libz not available!)
    fi
    ZLIB_LIBS=$LIBS
    LIBS=$_old_libs

    AC_SUBST(ZLIB_LIBS, [$ZLIB_LIBS])
fi

dnl Setup the platform
AC_ARG_ENABLE(platform,
              AS_HELP_STRING([--platform],
                             [Platform upon which we are compiling]),
              AS_CASE([$enableval],
                       [aix],  [LIBRARYONE_PLATFORM=aix],
                       [arcos],  [LIBRARYONE_PLATFORM=aix=arcos],
                       [linux],  [LIBRARYONE_PLATFORM=linux],
                       [mac], [LIBRARYONE_PLATFORM=mac],
                       [solaris],  [LIBRARYONE_PLATFORM=solaris],
                       [sunos],  [LIBRARYONE_PLATFORM=sunos],
                       [*],   [AC_MSG_ERROR(Please specify the platform)]))

dnl Set up rom.io
AC_ARG_ENABLE([romio],
  AS_HELP_STRING(--enable-romio, enable support for the optional romio library @<:@default=yes@:>@),
                 [case "$enableval" in
                    yes)  ROMIO_ENABLED=yes ;;
                    no)   ROMIO_ENABLED=no ;;
                    *)    AC_MSG_ERROR(--enable-romio=$enableval is invalid; choices are "y" and "n") ;;
                  esac],[ROMIO_ENABLED=yes])

if test "$ROMIO_ENABLED" = yes; then
  AC_DEFINE([HAVE_ROMIO],1,[Define if you have the rom.io library.])
fi

AC_CONFIG_HEADERS(include/libraryone/base/configtmp.h:include/libraryone/base/config.h.in)
AX_PREFIX_CONFIG_H(include/libraryone/base/config.h,LIBRARYONE,include/libraryone/base/configtmp.h)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
