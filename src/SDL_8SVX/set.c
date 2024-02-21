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

#include "set.h"
#include <stdlib.h>
#include <lib8svx/8svx.h>

IFF_Bool SDL_8SVX_initSetFromFd(SDL_8SVX_Set *set, FILE *file)
{
    IFF_Chunk *chunk = _8SVX_readFd(file);
    return SDL_8SVX_initSetFromIFFChunk(set, chunk, TRUE);
}

IFF_Bool SDL_8SVX_initSetFromFilename(SDL_8SVX_Set *set, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    int status = SDL_8SVX_initSetFromFd(set, file);
    fclose(file);
    return status;
}

IFF_Bool SDL_8SVX_initSet(SDL_8SVX_Set *set, const char *filename)
{
    if(filename == NULL)
        return SDL_8SVX_initSetFromFd(set, stdin);
    else
        return SDL_8SVX_initSetFromFilename(set, filename);
}

IFF_Bool SDL_8SVX_initSetFromIFFChunk(SDL_8SVX_Set *set, IFF_Chunk *chunk, IFF_Bool mustFreeChunk)
{
    set->chunk = chunk;
    set->mustFreeChunk = mustFreeChunk;
    set->_8svxInstruments = _8SVX_extractInstruments(chunk, &set->instrumentsLength);

    return _8SVX_checkInstruments(chunk, set->_8svxInstruments, set->instrumentsLength);
}

SDL_8SVX_Set *SDL_8SVX_createSetFromFd(FILE *file)
{
    SDL_8SVX_Set *set = (SDL_8SVX_Set*)malloc(sizeof(SDL_8SVX_Set));

    if(set != NULL)
    {
        if(!SDL_8SVX_initSetFromFd(set, file))
        {
            SDL_8SVX_freeSet(set);
            return NULL;
        }
    }

    return set;
}

SDL_8SVX_Set *SDL_8SVX_createSetFromFilename(const char *filename)
{
    SDL_8SVX_Set *set = (SDL_8SVX_Set*)malloc(sizeof(SDL_8SVX_Set));

    if(set != NULL)
    {
        if(!SDL_8SVX_initSetFromFilename(set, filename))
        {
            SDL_8SVX_freeSet(set);
            return NULL;
        }
    }

    return set;
}

SDL_8SVX_Set *SDL_8SVX_createSet(const char *filename)
{
    SDL_8SVX_Set *set = (SDL_8SVX_Set*)malloc(sizeof(SDL_8SVX_Set));

    if(set != NULL)
    {
        if(!SDL_8SVX_initSet(set, filename))
        {
            SDL_8SVX_freeSet(set);
            return NULL;
        }
    }

    return set;
}

SDL_8SVX_Set *SDL_8SVX_createSetFromIFFChunk(IFF_Chunk *chunk, IFF_Bool mustFreeChunk)
{
    SDL_8SVX_Set *set = (SDL_8SVX_Set*)malloc(sizeof(SDL_8SVX_Set));

    if(set != NULL)
    {
        if(!SDL_8SVX_initSetFromIFFChunk(set, chunk, mustFreeChunk))
        {
            SDL_8SVX_freeSet(set);
            return NULL;
        }
    }

    return set;
}

SDL_8SVX_Instrument *SDL_8SVX_createInstrumentFromSet(const SDL_8SVX_Set *set, const unsigned int index, Uint16 format, int frequency)
{
    if(index < set->instrumentsLength)
        return SDL_8SVX_createInstrument(set->_8svxInstruments[index], format, frequency);
    else
        return NULL;
}

void SDL_8SVX_cleanupSet(SDL_8SVX_Set *set)
{
    _8SVX_freeInstruments(set->_8svxInstruments, set->instrumentsLength);

    if(set->mustFreeChunk)
        _8SVX_free(set->chunk);
}

void SDL_8SVX_freeSet(SDL_8SVX_Set *set)
{
    if(set != NULL)
    {
        SDL_8SVX_cleanupSet(set);
        free(set);
    }
}
