AC_PREREQ(2.61)
AC_INIT([SDL_8SVX], m4_esyscmd([echo -n $(cat ./version)$VERSION_SUFFIX]))
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([1.7.2 -Wall -Werror])

# Checks for programs
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
PKG_PROG_PKG_CONFIG

# Checks for libiff library
LIBIFF_REQUIRED=0.1
PKG_CHECK_MODULES(LIBIFF, libiff >= $LIBIFF_REQUIRED)
AC_SUBST(LIBIFF_CFLAGS)
AC_SUBST(LIBIFF_LIBS)

# Checks for lib8svx library
LIB8SVX_REQUIRED=0.1
PKG_CHECK_MODULES(LIB8SVX, lib8svx >= $LIB8SVX_REQUIRED)
AC_SUBST(LIB8SVX_CFLAGS)
AC_SUBST(LIB8SVX_LIBS)

# Checks for libresample library
LIBRESAMPLE_REQUIRED=0.1.3
PKG_CHECK_MODULES(LIBRESAMPLE, libresample >= $LIBRESAMPLE_REQUIRED)
AC_SUBST(LIBRESAMPLE_CFLAGS)
AC_SUBST(LIBRESAMPLE_LIBS)

# Checks for SDL library
AC_CHECK_PROG([SDL_CONFIG], [sdl-config], [sdl-config])

if test -n "$SDL_CONFIG"; then
    if test -z "$SDL_CFLAGS"; then
        SDL_CFLAGS=`$SDL_CONFIG --cflags`
    fi
    
    if test -z "$SDL_LIBS"; then
        SDL_LIBS=`$SDL_CONFIG --libs`
    fi
fi

AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

# Output
AC_CONFIG_FILES([
Makefile
src/Makefile
src/SDL_8SVX/Makefile
src/8svxplayer/Makefile
doc/Makefile
doc/man/Makefile
])
AC_OUTPUT
