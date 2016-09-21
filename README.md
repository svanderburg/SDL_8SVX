SDL_8SVX
========
SDL_8SVX is a package containing a library for playing 8SVX instruments as
well as command-line player: `8svxplayer`.

Prerequisites
=============
In order to build and use this package the following libraries are required:

* [libiff](http://github.com/svanderburg/libiff), in order to parse IFF files
* [lib8svx](https://github.com/svanderburg/lib8svx), in order to understand 8SVX
  application chunks, fibonacci delta compression/decompression and to
  conveniently access 8SVX instrument properties
* [SDL](http://www.libsdl.org), is used as a portability layer to handle input
  and graphics
* [SDL_mixer](http://www.libsdl.org/projects/SDL_mixer), is used for mixing
  audio chunks
* [libresample](http://ftp.debian.org/debian/pool/main/libr/libresample), is
  used to resample the samples to acceptable frequencies. I have downloaded the
  Debian version and the corresponding Debian patches providing a CMake build
  interface

Installation
============
Compilation and installation of this library is straight forward, by using the
standard GNU autotools build instructions:

    $ ./configure
    $ make
    $ make install

More details about the installation process can be found in the `INSTALL` file
included in this package.

Using the SDL_8SVX API
======================
The `SDL_8SVX` package provides an API that can be used to read IFF files
containing 8SVX instruments and allows easy usage of these instruments in SDL
applications.

Full API documentation can be found in the `doc/apidox` directory of this
package.

Generating an instruments set
-----------------------------
An 8SVX file typically provides one single FORM representing an instrument, but
could also encapsulate multiple instruments and other types of forms, in so
called "IFF scrap files". The `SDL_8SVX_Set` struct provides an interface to
access all 8SVX instruments in a particular IFF file:

```C
#include <set.h>

SDL_8SVX_Set *set = SDL_8SVX_createSetFromFilename("somefile.IFF");

if(set != NULL && set->instrumentsLength > 0)
{
    /* Open an instrument */
    
    return 0;
}
else
    return 1; /* Cannot find any instruments to render samples from */
```

The above code fragment generates an instruments set directly from a file with a
given filename. In addition to generating sets from file names, it is also
possible to generate a set from a file descriptor (through:
`SDL_8SVX_createSetFromFd()`) or an `IFF_Chunk` (through:
`SDL_8SVX_createSetFromIFFChunk()`).

When the work is done, a set must be deallocated from heap memory, through:

```C
SDL_8SVX_freeSet(set);
```

Composing an instrument for audio playback
------------------------------------------
Using the set API, we can retrieve an instrument from the IFF file to render
samples from to the audio buffer:

```C
#include <set.h>

SDL_8SVX_Instrument *instrument = SDL_8SVX_createInstrumentFromSet(set, 0, AUDIO_S16SYS, 22050);
```

The above function invocation generates an `SDL_8SVX_Instrument` struct from the
first entry in the IFF file, in signed 16-bit format (with the same endianness
as the host system) using a sample rate frequency of `22050`.

We can obtain the corresponding audio sample chunks from the generated
`SDL_8SVX_Instrument` struct and pass them to an audio channel:

```C
#include <stdio.h>
#include <SDL_mixer.h>
#include <instrument.h>

unsigned int i;

/* Iterate over all sample audio chunks provided by the instrument */
for(i = 0; i < instrument->mixChunksLength; i++)
{
    int channel;
    
    /* Fetch a sample */
    Mix_Chunk *mixChunk = &instrument->mixChunks[i];
    
    /* Play the sample on channel 0 */
    if((channel = Mix_PlayChannel(-1, mixChunk, 0)) == -1)
    {
        fprintf(stderr, "Cannot play sample!\n");
        return 1;
    }

    /* Wait for the channel to finish playing */
    while(Mix_Playing(channel) != 0);
}
```

Consult the `SDL_mixer` API documentation for more details on how to set up the
required audio infrastructure.

When the work is done, we must deallocate the instrument with the following
instruction:

```C
#include <instrument.h>

SDL_8SVX_freeInstrument(instrument);
```

8SVX player command-line utility
================================
This package also includes a command-line utility: `8svxplayer` that exposes
most of the API's features as command-line options. For more information, run:

    $ 8svxplayer --help

License
=======
This library is available under the zlib license
