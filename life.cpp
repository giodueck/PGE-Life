#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "getopt.h"
#include "about.h"

#include <cstdlib>
#include <vector>

// Rules. Conway's Life is B3/S23
bool Birth[9], Survival[9];

// Options
int opt;
extern char *optarg;
extern int optopt;

// Switches
bool oRandom = false,
     oGenerateSettings = false,
     oHelp = false,
     oVersion = false,
     oVsync = false;

// Options with arguments
bool oLoadSeed = false,
     oLoadSettings = false,
     oUpsLimit = false,
     oPixelSize = false,
     oLoadPreset = false,
     oRules = false,
     oCustomScreenSize = false,
     oCustomTrailTime = false,
     oCustomTrailColor0 = false,
     oCustomTrailColor1 = false;

// Arguments for said options
const char *seedFilename,
    *settingsFilename;
int upsLimit,
    pixelSize,
    preset;
const char *ruleStr;
int customWidth, cusstomHeight,
    trailTime,
    trailC0, trailC1;

// Read custom rules from arguments
void SetRules(char *arg)
{
    bool *currRule = nullptr;
    for (int c = 0; arg[c] != '\0'; c++)
    {
        switch (arg[c])
        {
        case 'b':
        case 'B':
            currRule = Birth;
            break;
        case 's':
        case 'S':
            currRule = Survival;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            currRule[arg[c] - '0'] = true;
            break;
        }
    }
}

class Life : public olc::PixelGameEngine
{
public:
    Life()
    {
        sAppName = std::string(APPNAME);
    }

private:
    const int SETUP = 0, SIMULATION = 1;
    int state = SETUP;

    std::vector<bool> currentGen;
    std::vector<bool> nextGen;
    std::vector<int> trail;
    std::vector<bool> seed;

    olc::Pixel livePixel = olc::WHITE;
    olc::Pixel deadPixel = olc::BLACK;
    const int trailTime = 6;
    std::vector<float> lerpValues;
    olc::Pixel trailRange[2] = {olc::BLUE, olc::CYAN};

    bool bContinue = false;
    bool bStep = false;

    float fGoalTime, fCurrTime;

    bool GetCell(int x, int y)
    {
        if (x < 0)
            x += ScreenWidth();
        else if (x >= ScreenWidth())
            x -= ScreenWidth();
        if (y < 0)
            y += ScreenHeight();
        else if (y >= ScreenHeight())
            y -= ScreenHeight();
        return currentGen[y * ScreenWidth() + x];
    }

    void SetCell(int x, int y, bool val)
    {
        if (x < 0)
            x += ScreenWidth();
        else if (x >= ScreenWidth())
            x -= ScreenWidth();
        if (y < 0)
            y += ScreenHeight();
        else if (y >= ScreenHeight())
            y -= ScreenHeight();
        nextGen[y * ScreenWidth() + x] = val;
    }

    void UpdateTrails()
    {
        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                int idx = y * ScreenWidth() + x;
                // if cell just died
                if (currentGen[idx] && !nextGen[idx])
                {
                    trail[idx] = trailTime;
                }
                // else if cell remained dead
                else if (!nextGen[idx] && trail[idx])
                {
                    trail[idx]--;
                }
            }
        }
    }

    olc::Pixel GetPixel(int x, int y)
    {
        if (GetCell(x, y))
            return livePixel;
        else if (trail[y * ScreenWidth() + x])
            return olc::PixelLerp(trailRange[0], trailRange[1], lerpValues[trailTime - trail[y * ScreenWidth() + x]]);
        else
            return deadPixel;
    }

    void Reset()
    {
        currentGen = seed;
        bStep = false;
        bContinue = false;
        state = SETUP;
        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                SetCell(x, y, false);
                trail[y * ScreenWidth() + x] = 0;
            }
        }
    }

public:
    bool OnUserCreate() override
    {
        srand(time(0));
        for (int i = 0; i < ScreenHeight(); i++)
        {
            for (int j = 0; j < ScreenWidth(); j++)
            {
                currentGen.push_back(rand() % 2 && oRandom);
                trail.push_back(0);
            }
        }
        nextGen = currentGen;
        seed = currentGen;

        for (float f = 0.0f; f < trailTime; f += 1)
        {
            lerpValues.push_back(f / (trailTime - 1));
        }

        if (oUpsLimit)
        {
            fGoalTime = 1.0f / upsLimit;
            fCurrTime = 0;
        }

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (oUpsLimit)
            fCurrTime += fElapsedTime;

        // Draw current generation
        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                Draw(x, y, GetPixel(x, y));
            }
        }

        if (state == SETUP)
        {
            int x = GetMouseX(), y = GetMouseY();

            // Mouse highlighting
            Draw(x, y, (GetPixel(x, y) == livePixel) ? olc::GREY : olc::DARK_GREY);

            // Set live cells with LMB, dead cells with RMB
            if (GetMouse(olc::Mouse::LEFT).bHeld && !GetMouse(olc::Mouse::RIGHT).bHeld)
            {
                currentGen[y * ScreenWidth() + x] = true;
            }
            else if (!GetMouse(olc::Mouse::LEFT).bHeld && GetMouse(olc::Mouse::RIGHT).bHeld)
            {
                currentGen[y * ScreenWidth() + x] = false;
            }

            // Clear screen
            if (GetKey(olc::CTRL).bHeld && GetKey(olc::C).bPressed)
            {
                currentGen = nextGen;
            }

            // Toggle continue with SPACE
            if (GetKey(olc::SPACE).bPressed)
            {
                bContinue = true;
                state = SIMULATION;
                seed = currentGen;
            }
            // Step through with ENTER
            if (GetKey(olc::ENTER).bPressed)
            {
                bStep = true;
                state = SIMULATION;
                seed = currentGen;
            }

            fCurrTime = 0;
        }
        else if (state == SIMULATION)
        {
            // Input is handled before simulation to catch input between simulation steps if oUpsLimit is set
            // Reset game
            if (GetKey(olc::CTRL).bHeld && GetKey(olc::R).bPressed)
            {
                Reset();
                return true;
            }
            // Toggle continue with SPACE
            if (GetKey(olc::SPACE).bPressed)
                bContinue = !bContinue;
            // Step through with ENTER
            if (GetKey(olc::ENTER).bPressed)
            {
                bContinue = false;
                bStep = true;
            }

            // UPS limit sets update limit, not fps limit
            if (oUpsLimit)
            {
                if (fCurrTime >= fGoalTime)
                    fCurrTime -= fGoalTime;
                else
                    return true;
            }

            if (!bContinue && !bStep)
            {
                return true;
            }

            // Compute next generation
            int n;
            for (int x = 0; x < ScreenWidth(); x++)
            {
                for (int y = 0; y < ScreenHeight(); y++)
                {
                    n = GetCell(x - 1, y - 1) + GetCell(x, y - 1) + GetCell(x + 1, y - 1) +
                        GetCell(x - 1, y) /*    self           */ + GetCell(x + 1, y) +
                        GetCell(x - 1, y + 1) + GetCell(x, y + 1) + GetCell(x + 1, y + 1);

                    // Birth
                    if (!GetCell(x, y))
                        SetCell(x, y, Birth[n]);
                    // Survival
                    else
                        SetCell(x, y, Survival[n]);
                }
            }

            if (trailTime > 0)
                UpdateTrails();
            currentGen = nextGen;
            bStep = false;
        }
        return true;
    }
};

int main(int argc, char **argv)
{
    // Set rules
    if (argc == 1)
    {
        Birth[3] = true;
        Survival[2] = true;
        Survival[3] = true;
    }
    else
    {
        while ((opt = getopt(argc, argv, ":vrR:u:y")) != -1)
        {
            switch (opt)
            {
            case 'v':
                oVersion = true;
                break;
            case 'r':
                oRandom = true;
                break;
            case 'R':
                oRules = true;
                SetRules(optarg);
                break;
            case 'u':
                oUpsLimit = true;
                upsLimit = atoi(optarg);
                if (upsLimit < 1)
                {
                    fprintf(stderr, "Bad argument: %d\nOption -m takes a positive integer argument!\n", upsLimit);
                    fprintf(stderr, "Usage: %s [-v] [-m <n>] [-r] [-R <rule>] [-y]\n", argv[0]);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'y':
                oVsync = true;
                break;
            case ':':
                std::cerr << "Option -" << char(optopt) << " is missing an argument!\n";
            default: // '?'
                fprintf(stderr, "Usage: %s [-v] [-r] [-R <rule>] [-u <n>] [-y]\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }

        if (oVersion || oHelp)
        {
            if (oVersion)
                printVersion();
            //help
        }

        if (!oRules)
        {
            // Default Life rules
            SetRules((char *)"B3S23");
        }
    }

    if (!oVersion && !oHelp)
    {
        Life game;
        if (game.Construct(240, 160, 4, 4, false, oVsync))
            game.Start();
    }

    return EXIT_SUCCESS;
}
