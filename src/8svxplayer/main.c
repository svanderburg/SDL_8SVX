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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"

#define TRUE 1
#define FALSE 0

static void printUsage(const char *command)
{
    printf("Usage: %s [OPTION] [file.8SVX]\n\n", command);
    
    printf("The command `8svxviewer' plays 8SVX instrument samples stored inside an IFF\n");
    printf("file. If no file is given, it reads from the standard input.\n\n");
    
    printf("Options:\n");
    printf("  -i, --instrument-number=NUM  Play samples from the provided 8SVX instrument\n");
    printf("                               entry in the IFF file (by default, it examines\n");
    printf("                               all instruments)\n");
    printf("  -s, --sample-number=NUM      Play the n-th sample from an 8SVX instrument (by\n");
    printf("                               default, it plays all samples)\n");
    printf("      --frequency=NUM          Sample frequency (defaults to: 22050)\n");
    printf("  -h, --help                   Shows the usage of the command to the user\n");
    printf("  -v, --version                Shows the version of the command to the user\n");
}

static void printVersion(const char *command)
{
    printf("%s (" PACKAGE_NAME ") " PACKAGE_VERSION "\n\n", command);
    printf("Copyright (C) 2012-2015 Sander van der Burg\n");
}

int main(int argc, char *argv[])
{
    /* Declarations */
    int c, option_index = 0;
    struct option long_options[] =
    {
        {"instrument-number", required_argument, 0, 'i'},
        {"sample-number", required_argument, 0, 's'},
        {"frequency", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };
    char *filename;
    unsigned int playAllInstruments = TRUE;
    unsigned int instrumentNumber = 0;
    unsigned int playAllSamples = TRUE;
    unsigned int sampleNumber = 0;
    int frequency = 22050;

    /* Parse command-line options */
    while((c = getopt_long(argc, argv, "i:s:f:hv", long_options, &option_index)) != -1)
    {
        switch(c)
        {
            case 'i':
                playAllInstruments = FALSE;
                instrumentNumber = atoi(optarg);
                break;
            case 's':
                playAllSamples = FALSE;
                sampleNumber = atoi(optarg);
                break;
            case 'f':
                frequency = atoi(optarg);
                break;
            case 'h':
            case '?':
                printUsage(argv[0]);
                return 0;
            case 'v':
                printVersion(argv[0]);
                return 0;
        }
    }
    
    /* Validate non options */
    
    if(optind >= argc)
        filename = NULL;
    else
        filename = argv[optind];
    
    return SDL_8SVX_play8SVXSamples(filename, playAllInstruments, instrumentNumber, playAllSamples, sampleNumber, frequency);
}
