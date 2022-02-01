#include "about.h"
#include <cstdio>
#include <cstdlib>

void printVersion()
{
    printf("%s version %d.%d%s\nMade by %s\n", APPDESC, MAJOR, MINOR, POSTFIX, AUTHOR);
    printf("\nPowered by olc::PixelGameEngine\n\tCopyright 2018 - 2021 OneLoneCoder.com\n");
    printf("\nSome parts of the code were taken from the University of California\n\tCopyright (c) 1987, 1993, 1994\n\tThe Regents of the University of California.  All rights reserved.");

    exit(EXIT_SUCCESS);
}

void printHelp(bool extended)
{
    if (!extended)
    {
        fprintf(stderr, "'%s -h' for help\n", APPNAME);
        return;
    }
    printf("Usage: %s [-h] [-v] [-r] [-R <rule>] [-t <n>] [-u <n>] [-y]\n\n", APPNAME);
    printf("    Options:\n");
    printf("        -h          Print this help menu and exit.\n");
    printf("        -r          Generate random starting generation on start-up.\n");
    printf("        -R <rule>   Specify a Life-like rule. Game of Life rules are default.\n");
    printf("                    Format: B<[0|1|...|8]>S<[0|1|...|8]>\n");
    printf("                    Example: for GoL '-R B3S23', i.e. dead cell are born with 3 neighbors,\n");
    printf("                    live cells survive with 2 or 3 neighbors.\n");
    printf("        -t <n>      Specify the length of colored trails left by dead cells.\n");
    printf("                    Set 0 to disable trails, default 6.\n");
    printf("        -u <n>      Specify the updates per second. Unlimited by default.\n");
    printf("        -v          Print version information and credits and exit.\n");
    printf("        -y          Enable VSync.\n");

    exit(EXIT_SUCCESS);
}