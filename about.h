#ifndef LIFE_ABOUT_H
#define LIFE_ABOUT_H

#define MAJOR 1
#define MINOR 1
#define POSTFIX (char*)"-indev"

#define APPNAME (char*)"life"

#define APPDESC (char*)"PGE-Life"

#define AUTHOR (char*)"giodueck"

void printVersion();

void printHelp(bool extended = false);

#endif // LIFE_ABOUT_H