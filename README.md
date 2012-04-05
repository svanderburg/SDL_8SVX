SDL_8SVX
========
SDL_8SVX is a package containing a library for playing 8SVX instruments as
well as command-line player: `8svxplayer`.

Prerequisites
=============
In order to build and use this package the following libraries are required:

* `libiff`, in order to parse IFF files
* `lib8svx`, in order to understand 8SVX application chunks, fibonacci delta compression/decompression and to conveniently access 8SVX instrument properties
* [SDL](http://www.libsdl.org), is used as a portability layer to handle input and graphics
* [SDL_mixer](http://www.libsdl.org/projects/SDL_mixer), is used for mixing audio chunks
* [libresample](http://ftp.debian.org/debian/pool/main/libr/libresample), is used to resample the samples to acceptable frequencies. I have downloaded the Debian version and I have applied the Debian patches, which provides a CMake build interface

Installation
============
Compilation and installation of this library is straight forward, by using the
standard GNU autotools build instructions:

    $ ./configure
    $ make
    $ make install

More details about the installation process can be found in the `INSTALL` file
included in this package.

License
=======
This library is available under the zlib license
