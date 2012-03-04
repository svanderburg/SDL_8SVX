/** 
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

#include <stdio.h>
#include <stdlib.h>
#include <8svx.h>
#include <8svxinstrument.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "samples.h"

int SDL_8SVX_play8SVXInstrument(const char *filename)
{
    IFF_Chunk *chunk = _8SVX_read(filename);
    
    if(chunk == NULL)
    {
	fprintf(stderr, "Cannot open IFF file!\n");
	return 1;
    }
    else
    {
	unsigned int instrumentsLength;
	_8SVX_Instrument **instruments;
	unsigned int i;
    
	if(SDL_Init(SDL_INIT_AUDIO) == -1)
	{
	    fprintf(stderr, "Cannot initialise audio!\n");
	    return 1;
	}
	
	instruments = _8SVX_extractInstruments(chunk, &instrumentsLength);
	
	for(i = 0; i < instrumentsLength; i++)
	{
	    unsigned int j;
	    _8SVX_Instrument *instrument = instruments[i];
	    unsigned int mixChunksLength;
	    Mix_Chunk *mixChunks;
	    int frequency = 22050;
	    Uint16 format = AUDIO_S16SYS;
	    
	    /* Extract resampled mix chunks */
	    mixChunks = SDL_8SVX_createResampledMixChunks(instrument, format, frequency, &mixChunksLength);
	    
	    for(j = 0; j < mixChunksLength; j++)
	    {
		int channel;
		Mix_Chunk *mixChunk = &mixChunks[j];
		
		fprintf(stderr, "Octave: %d\n", j);
		
		if(Mix_OpenAudio(frequency, format, 1, 512) == -1)
		    fprintf(stderr, "Cannot open mixer channel!\n");
		
		if((channel = Mix_PlayChannel(-1, mixChunk, 0)) == -1)
		    fprintf(stderr, "Cannot play sample!\n");
		
		while(Mix_Playing(channel) != 0);
		
		Mix_CloseAudio();
	    }
	}
	
	SDL_Quit();
	
	_8SVX_freeInstruments(instruments, instrumentsLength);
	_8SVX_free(chunk);
    
	return 0;
    }
}
