#include "various.h"

float fmod(float D, int d)
{
    return (int)D % d + D - (int)D;
}

int RGBtoHSV(int R, int G, int B, float &H, float &S, float &V)
{
    float R_ = R / 255.0f, G_ = G / 255.0f, B_ = B / 255.0f;
    float Cmax = MAX(R_, MAX(G_, B_));
    float Cmin = MIN(R_, MIN(G_, B_));
    float delta = Cmax - Cmin;

    if (R_ < 0 || R_ > 255 || G_ < 0 || G_ > 255 || B_ < 0 || B_ > 255)
        return 1;

    // Hue
    if (delta == 0)
        H = 0;
    else if (Cmax == R_)
        H = 60.0f * fmod(((G_ - B_) / delta), 6);
    else if (Cmax == R_)
        H = 60 * (((B_ - R_) / delta) + 2);
    else // if (Cmax == R_)
        H = 60 * (((R_ - G_) / delta) + 4);

    // Saturation
    if (Cmax == 0)
        S = 0;
    else
        S = delta / Cmax;

    // Value
    V = Cmax;

    return 0;
}

int HSVtoRGB(float H, float S, float V, int &R, int &G, int &B)
{
    float C = S * V;
    float X = C * (1 - ABS(fmod(H / 60, 2) - 1));
    float m = V - C;

    if (H < 0 || H > 360 || S < 0 || S > 1 || V < 0 || V > 1)
        return 1;

    float R_, G_, B_;
    if (H >= 300)
        R_ = C, G_ = 0, B_ = X;
    else if (H >= 240)
        R_ = X, G_ = 0, B_ = C;
    else if (H >= 180)
        R_ = 0, G_ = X, B_ = C;
    else if (H >= 120)
        R_ = 0, G_ = C, B_ = X;
    else if (H >= 60)
        R_ = X, G_ = C, B_ = 0;
    else // if (H >= 0)
        R_ = C, G_ = X, B_ = 0;
    
    R = int((R_ + m) * 255);
    G = int((G_ + m) * 255);
    B = int((B_ + m) * 255);

    return 0;
}