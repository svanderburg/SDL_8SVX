lib_LTLIBRARIES = libSDL_8SVX.la
pkginclude_HEADERS = instrument.h set.h

libSDL_8SVX_la_SOURCES = instrument.c set.c
libSDL_8SVX_la_CFLAGS = $(LIBIFF_CFLAGS) $(LIB8SVX_CFLAGS) $(LIBRESAMPLE_CFLAGS) $(SDL2_CFLAGS) $(SDL2_MIXER_CFLAGS)
libSDL_8SVX_la_LIBADD = $(LIBIFF_LIBS) $(LIB8SVX_LIBS) $(LIBRESAMPLE_LIBS) $(SDL2_LIBS) $(SDL2_MIXER_LIBS) -lresample
