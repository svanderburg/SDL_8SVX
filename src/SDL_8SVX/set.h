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

/**
 * @brief An encapsulation of a set of instruments that originate from an IFF/8SVX file.
 */
struct SDL_8SVX_Set
{
    /** Reference to a parsed chunk originating from an IFF file */
    IFF_Chunk *chunk;

    /** An array extracted 8SVX instruments from an IFF file */
    _8SVX_Instrument **_8svxInstruments;

    /** Specifies the length of the 8SVX instruments array */
    unsigned int instrumentsLength;

    /* Indicates whether the chunk must be deallocated while freeing the set */
    IFF_Bool mustFreeChunk;
};

/**
 * Initializes a preallocated set by opening a file with a specific file
 * descriptor.
 *
 * @param set A preallocated set
 * @param file File descriptor
 * @return TRUE if the initialization succeeded, else FALSE
 */
IFF_Bool SDL_8SVX_initSetFromFd(SDL_8SVX_Set *set, FILE *file);

/**
 * Initializes a preallocated set by opening a file with a specified filename.
 *
 * @param set A preallocated set
 * @param filename Path to an IFF file to open
 * @return TRUE if the initialization succeeded, else FALSE
 */
IFF_Bool SDL_8SVX_initSetFromFilename(SDL_8SVX_Set *set, const char *filename);

/**
 * Initializes a preallocated set by opening a file with a specified filename or by reading from the standard input when no filename is given.
 *
 * @param set A preallocated set
 * @param filename Path to an IFF file to open or NULL to read from the standard input
 * @return TRUE if the initialization succeeded, else FALSE
 */
IFF_Bool SDL_8SVX_initSet(SDL_8SVX_Set *set, const char *filename);

/**
 * Initializes a preallocated set by parsing an IFF chunk.
 *
 * @param set A preallocated set
 * @param chunk IFF chunk originating from a parsed file
 * @param mustFreeChunk Indicates whether the provided chunk must be freed from memory while freeing the set
 * @return TRUE if the set was successfully generated, else FALSE
 */
IFF_Bool SDL_8SVX_initSetFromIFFChunk(SDL_8SVX_Set *set, IFF_Chunk *chunk, IFF_Bool mustFreeChunk);

/**
 * Creates a set by opening a file with a specific file descriptor.
 *
 * @param file File descriptor
 * @return An SDL_8SVX_Set instance or NULL in case of an error. The resulting set must be freed with SDL_8SVX_freeSet()
 */
SDL_8SVX_Set *SDL_8SVX_createSetFromFd(FILE *file);

/**
 * Creates a set by opening a file with a specified filename.
 *
 * @param filename Path to an IFF file to open
 * @return An SDL_8SVX_Set instance or NULL in case of an error. The resulting set must be freed with SDL_8SVX_freeSet()
 */
SDL_8SVX_Set *SDL_8SVX_createSetFromFilename(const char *filename);

/**
 * Creates a set by opening a file with a specified filename or from the standard input when no filename is provided.
 *
 * @param filename Path to an IFF file to open or NULL to read from the standard input
 * @return An SDL_8SVX_Set instance or NULL in case of an error. The resulting set must be freed with SDL_8SVX_freeSet()
 */
SDL_8SVX_Set *SDL_8SVX_createSet(const char *filename);

/**
 * Creates a set by parsing an IFF chunk.
 *
 * @param chunk IFF chunk originating from a parsed file
 * @param mustFreeChunk Indicates whether the provided chunk must be freed from memory while freeing the set
 * @return An SDL_8SVX_Set instance or NULL in case of an error. The resulting set must be freed with SDL_8SVX_freeSet()
 */
SDL_8SVX_Set *SDL_8SVX_createSetFromIFFChunk(IFF_Chunk *chunk, IFF_Bool mustFreeChunk);

/**
 * Creates an resampled instrument from a given an instrument in a set.
 *
 * @param set An SDL_8SVX_Set containing instruments
 * @param index Index of an instrument in the set
 * @param format Defines the sample format of the instruments
 * @param frequency Defines the sample frequency of the instrument samples
 * @return An SDL_8SVX_Instrument instance or NULL in case of an error. The result must be freed by invoking SDL_8SVX_freeInstrument()
 */
SDL_8SVX_Instrument *SDL_8SVX_createInstrumentFromSet(const SDL_8SVX_Set *set, const unsigned int index, Uint16 format, int frequency);

/**
 * Clears all properties of a set from memory.
 *
 * @param set An SDL_8SVX_Set containing instruments
 */
void SDL_8SVX_cleanupSet(SDL_8SVX_Set *set);

/**
 * Frees a set from memory.
 *
 * @param set An SDL_8SVX_Set containing instruments
 */
void SDL_8SVX_freeSet(SDL_8SVX_Set *set);

#ifdef __cplusplus
}
#endif

#endif
