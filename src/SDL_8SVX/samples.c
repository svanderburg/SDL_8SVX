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

#include "samples.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <lib8svx/fibdelta.h>
#include <SDL.h>
#include <libresample.h>

static Mix_Chunk *createMixChunks(_8SVX_Instrument *instrument, unsigned int *mixChunksLength)
{
    unsigned int samplesLength;
    _8SVX_Sample *samples = _8SVX_extractSamples(instrument, &samplesLength);
    Mix_Chunk *mixChunks = (Mix_Chunk*)malloc(samplesLength * sizeof(Mix_Chunk));
    unsigned int i;
    
    for(i = 0; i < samplesLength; i++)
    {
	Mix_Chunk *mixChunk = &mixChunks[i];
	
	mixChunk->allocated = FALSE;
	mixChunk->abuf = (Uint8*)samples[i].body;
	mixChunk->alen = samples[i].sampleSize;
	mixChunk->volume = instrument->voice8Header->volume * 128 / _8SVX_MAX_VOLUME;
    }
    
    free(samples);
    
    *mixChunksLength = samplesLength;
    return mixChunks;
}

static void resampleMixChunkFrequency(_8SVX_Instrument *instrument, Mix_Chunk *mixChunk, int frequency)
{
    unsigned int i;
    void *handle;
    double factor = (double)frequency / instrument->voice8Header->samplesPerSec;
    float *inBuffer = (float*)malloc(mixChunk->alen * sizeof(float));
    int inBufferUsed;
    int outBufferLen = ceil(mixChunk->alen * factor);
    float *outBuffer = (float*)malloc(outBufferLen * sizeof(float));
    Uint8 *abuf = (Uint8*)malloc(outBufferLen * sizeof(Uint8));
    
    /* Open resample handle */
    handle = resample_open(TRUE, factor, factor);
    
    /* Convert bytes to float */
    for(i = 0; i < mixChunk->alen; i++)
	inBuffer[i] = ((Sint8)mixChunk->abuf[i] + 0.5f) / 127.5f;

    /* Do resampling */
    resample_process(handle, factor, inBuffer, mixChunk->alen, TRUE, &inBufferUsed, outBuffer, outBufferLen);
    
    /* Convert float to bytes */
    for(i = 0; i < outBufferLen; i++)
	abuf[i] = (127.5f * outBuffer[i]) - 0.5f;
    
    /* Set the chunk data to the resampled value */
    mixChunk->allocated = TRUE;
    mixChunk->alen = outBufferLen;
    mixChunk->abuf = abuf;
    
    /* Cleanup */
    resample_close(handle);
    free(inBuffer);
    free(outBuffer);
}

static void resampleMixChunkFormat(Mix_Chunk *mixChunk, Uint16 format, int frequency)
{
    SDL_AudioCVT cvt;
    
    SDL_BuildAudioCVT(&cvt, AUDIO_S8, 1, frequency, format, 1, frequency);
    cvt.buf = malloc(mixChunk->alen * cvt.len_mult);
    cvt.len = mixChunk->alen;
    memcpy(cvt.buf, mixChunk->abuf, mixChunk->alen);
    
    SDL_ConvertAudio(&cvt);
    
    free(mixChunk->abuf);
    mixChunk->abuf = cvt.buf;
    mixChunk->alen = mixChunk->alen * cvt.len_mult;
}

Mix_Chunk *SDL_8SVX_createResampledMixChunks(_8SVX_Instrument *instrument, Uint16 format, int frequency, unsigned int *mixChunksLength)
{
    Mix_Chunk *mixChunks;
    unsigned int i;
    
    /* Decompress the instrument body chunk */
    _8SVX_unpackFibonacciDelta(instrument);

    /* Create mix chunks out of the sample data */
    mixChunks = createMixChunks(instrument, mixChunksLength);
    
    /* Resample the mix chunks */
    for(i = 0; i < *mixChunksLength; i++)
    {
	Mix_Chunk *mixChunk = &mixChunks[i];
	resampleMixChunkFrequency(instrument, mixChunk, frequency);
	resampleMixChunkFormat(mixChunk, format, frequency);
    }
    
    /* Return the resampled chunks */
    return mixChunks;
}
