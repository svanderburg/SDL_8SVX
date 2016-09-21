/*
 * Copyright (c) 2012 Sander van der Burg
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software in a
 * product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Sander van der Burg <svanderburg@gmail.com>
 */

#ifndef __SDL_8SVX_SET_H
#define __SDL_8SVX_SET_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDL_8SVX_Set SDL_8SVX_Set;

#include <stdio.h>
#include <SDL.h>
#include <lib8svx/8svxinstrument.h>
#include "instrument.h"

struct SDL_8SVX_Set
{
    IFF_Chunk *chunk;
    _8SVX_Instrument **_8svxInstruments;
    unsigned int instrumentsLength;
    int mustFreeChunk;
};

int SDL_8SVX_initSetFromFilename(SDL_8SVX_Set *set, const char *filename);

int SDL_8SVX_initSetFromFd(SDL_8SVX_Set *set, FILE *file);

int SDL_8SVX_initSetFromIFFChunk(SDL_8SVX_Set *set, IFF_Chunk *chunk, int mustFreeChunk);

SDL_8SVX_Set *SDL_8SVX_createSetFromFilename(const char *filename);

SDL_8SVX_Set *SDL_8SVX_createSetFromFd(FILE *file);

SDL_8SVX_Set *SDL_8SVX_createSetFromIFFChunk(IFF_Chunk *chunk, int mustFreeChunk);

SDL_8SVX_Instrument *SDL_8SVX_createInstrumentFromSet(const SDL_8SVX_Set *set, const unsigned int index, Uint16 format, int frequency);

void SDL_8SVX_cleanupSet(SDL_8SVX_Set *set);

void SDL_8SVX_freeSet(SDL_8SVX_Set *set);

#ifdef __cplusplus
}
#endif

#endif
