8svxplayer.1: main.c
	$(HELP2MAN) --output=$@ --no-info --name 'Play a collection of 8SVX instruments inside an IFF file' --libtool ./8svxplayer

bin_PROGRAMS = 8svxplayer
noinst_HEADERS = player.h
man1_MANS = 8svxplayer.1

8svxplayer_SOURCES = main.c player.c
8svxplayer_LDADD = ../SDL_8SVX/libSDL_8SVX.la $(LIBIFF_LIBS) $(LIB8SVX_LIBS) $(LIBRESAMPLE_LIBS) $(SDL2_LIBS) $(SDL2_MIXER_LIBS)
8svxplayer_CFLAGS = -I../SDL_8SVX $(LIBIFF_CFLAGS) $(LIB8SVX_CFLAGS) $(SDL2_CFLAGS) $(SDL2_MIXER_CFLAGS)

EXTRA_DIST = 8svxplayer.1
