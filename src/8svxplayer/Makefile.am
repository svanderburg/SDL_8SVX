bin_PROGRAMS = 8svxplayer
noinst_HEADERS = player.h

8svxplayer_SOURCES = main.c player.c
8svxplayer_LDADD = ../SDL_8SVX/libSDL_8SVX.la $(LIBIFF_LIBS) $(LIB8SVX_LIBS) $(LIBRESAMPLE_LIBS) $(SDL_LIBS) -lSDL_mixer
8svxplayer_CFLAGS = -I../SDL_8SVX $(LIBIFF_CFLAGS) $(LIB8SVX_CFLAGS) $(SDL_CFLAGS)
