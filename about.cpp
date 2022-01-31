#include "about.h"
#include <cstdio>
#include <cstdlib>

void printVersion()
{
    printf("%s version %s%d.%d\nMade by %s\n", APPNAME, PREFIX, MAJOR, MINOR, AUTHOR);
    printf("\nPowered by olc::PixelGameEngine\n\tCopyright 2018 - 2021 OneLoneCoder.com\n");
    printf("\nSome parts of the code were taken from the University of California\n\tCopyright (c) 1987, 1993, 1994\n\tThe Regents of the University of California.  All rights reserved.");

    exit(EXIT_SUCCESS);
}