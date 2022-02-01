#ifndef VARIOUS_H
#define VARIOUS_H

// Max/Min/Abs macros
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define ABS(a) (((a) < 0) ? -(a) : (a))

// Floating point modulo
float fmod(float D, int d);

// Convert between the color representations
// RGB values go from 0 to 255, H goes from 0 to 360, and SV go from 0 to 1
// Return: 0 -> ok
//         1 -> incorrect input
int RGBtoHSV(int R, int G, int B, float& H, float& S, float& V);

// Convert between the color representations
// RGB values go from 0 to 255, H goes from 0 to 360, and SV go from 0 to 1
// Return: 0 -> ok
//         1 -> incorrect input
int HSVtoRGB(float H, float S, float V, int& R, int& G, int& B);

#endif // VARIOUS_H