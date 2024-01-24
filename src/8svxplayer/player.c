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

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "set.h"

static int playSample(Mix_Chunk *mixChunk, unsigned int octave)
{
    int channel;

    fprintf(stderr, "Octave: %u\n", octave);

    if((channel = Mix_PlayChannel(-1, mixChunk, 0)) == -1)
    {
        fprintf(stderr, "Cannot play sample!\n");
        return FALSE;
    }

    /* Wait for the channel to finish playing */
    while(Mix_Playing(channel) != 0)
        ;

    return TRUE;
}

static int playSamplesFromInstrument(SDL_8SVX_Instrument *instrument, unsigned int playAllSamples, unsigned int sampleNumber)
{
    if(playAllSamples)
    {
        unsigned int i;

        for(i = 0; i < instrument->mixChunksLength; i++)
        {
            Mix_Chunk *mixChunk = &instrument->mixChunks[i];

            if(!playSample(mixChunk, i))
                return FALSE;
        }

        return TRUE;
    }
    else
    {
        if(sampleNumber > instrument->mixChunksLength)
        {
            fprintf(stderr, "Sample with index: %d does not exist. Valid ranges are: 0 - %d\n", sampleNumber, instrument->mixChunksLength);
            return FALSE;
        }
        else
        {
            Mix_Chunk *mixChunk = &instrument->mixChunks[sampleNumber];
            return playSample(mixChunk, sampleNumber);
        }
    }
}

int SDL_8SVX_play8SVXSamples(const char *filename, unsigned int playAllInstruments, unsigned int instrumentNumber, unsigned int playAllSamples, unsigned int sampleNumber, int frequency)
{
    Uint16 format = AUDIO_S16SYS;
    SDL_8SVX_Set *set;
    int exitStatus = 0;

    /* Open the 8SVX file and generate a set from it*/
    if(filename == NULL)
        set = SDL_8SVX_createSetFromFd(stdin);
    else
        set = SDL_8SVX_createSetFromFilename(filename);

    if(set == NULL)
    {
        fprintf(stderr, "Error parsing 8SVX file!\n");
        return 1;
    }

    /* Initialise audio sub systems */
    if(SDL_Init(SDL_INIT_AUDIO) == -1)
    {
        fprintf(stderr, "Cannot initialise audio!\n");
        SDL_8SVX_freeSet(set);
        return 1;
    }

    if(Mix_OpenAudio(frequency, format, 1, 512) == -1)
    {
        fprintf(stderr, "Cannot open mixer channel!\n");
        SDL_8SVX_freeSet(set);
        SDL_Quit();
        return 1;
    }

    if(playAllInstruments)
    {
        /* Play the specified samples in all instruments */
        unsigned int i;

        for(i = 0; i < set->instrumentsLength; i++)
        {
            SDL_8SVX_Instrument *instrument = SDL_8SVX_createInstrumentFromSet(set, i, format, frequency);

            if(instrument == NULL)
            {
                fprintf(stderr, "Cannot create instrument!\n");
                exitStatus = 1;
            }
            else
            {
                if(!playSamplesFromInstrument(instrument, playAllSamples, sampleNumber))
                    exitStatus = 1;

                SDL_8SVX_freeInstrument(instrument);

                if(exitStatus != 0)
                    break;
            }
        }
    }
    else
    {
        if(instrumentNumber > set->instrumentsLength)
        {
            fprintf(stderr, "Instrument with index: %d does not exist. Valid ranges are: 0 - %d\n", instrumentNumber, set->instrumentsLength - 1);
            exitStatus = 1;
        }
        else
        {
            /* Play the specified samples in the specified instrument */
            SDL_8SVX_Instrument *instrument = SDL_8SVX_createInstrumentFromSet(set, instrumentNumber, format, frequency);

            if(instrument == NULL)
            {
                fprintf(stderr, "Cannot create instrument!\n");
                exitStatus = 1;
            }
            else
            {
                if(!playSamplesFromInstrument(instrument, playAllSamples, sampleNumber))
                    exitStatus = 0;

                SDL_8SVX_freeInstrument(instrument);
            }
        }
    }

    /* Clean up */
    Mix_CloseAudio();

    SDL_8SVX_freeSet(set);
    SDL_Quit();

    /* Return exit status */
    return exitStatus;
}
