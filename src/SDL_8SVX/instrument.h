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

#ifndef __SDL_8SVX_INSTRUMENT_H
#define __SDL_8SVX_INSTRUMENT_H

typedef struct SDL_8SVX_Instrument SDL_8SVX_Instrument;

#include <lib8svx/8svxinstrument.h>
#include <SDL_mixer.h>

/**
 * @brief Encapsulates the properties of a resampled instrument
 */
struct SDL_8SVX_Instrument
{
    /** Reference to the 8SVX intrument from which this instrument is generated */
    _8SVX_Instrument *instrument;
    
    /** Array of mix chunks each representing audio samples for each octave */
    Mix_Chunk *mixChunks;
    
    /** Contains the length of the mix chunks array */
    unsigned int mixChunksLength;
    
    /** Defines the sample format of the instruments */
    Uint16 format;
    
    /** Defines the sample frequency of the instrument samples */
    int frequency;
};

/**
 * Creates an resampled instrument from a given 8SVX instrument.
 *
 * @param format Defines the sample format of the instruments
 * @param frequency Defines the sample frequency of the instrument samples
 * @return An SDL_8SVX_Instrument instance or NULL in case of an error. The result must be freed by invoking SDL_8SVX_freeInstrument()
 */
SDL_8SVX_Instrument *SDL_8SVX_createInstrument(_8SVX_Instrument *instrument, Uint16 format, int frequency);

/**
 * Frees the resampled instrument from memory
 *
 * @param instrument An SDL_8SVX_Instrument instance
 */
void SDL_8SVX_freeInstrument(SDL_8SVX_Instrument *instrument);

#endif
