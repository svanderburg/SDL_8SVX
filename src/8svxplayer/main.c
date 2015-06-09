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
#include "player.h"

static void printUsage(const char *command)
{
    printf("Usage: %s [OPTION] [file.8SVX]\n\n", command);
    
    printf("The command `8svxviewer' plays 8SVX instruments stored inside an IFF file. If no file is\n");
    printf("given, it reads from the standard input.\n\n");
    
    printf("Options:\n");
    printf("  -h, --help       Shows the usage of the command to the user\n");
    printf("  -v, --version    Shows the version of the command to the user\n");
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
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };
    char *filename;

    /* Parse command-line options */
    while((c = getopt_long(argc, argv, "hv", long_options, &option_index)) != -1)
    {
        switch(c)
        {
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
    
    return SDL_8SVX_play8SVXInstrument(filename);
}
