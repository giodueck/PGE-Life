# Usage
Execute `life.exe` to launch the app.\
Features:
- Draw live and dead cells using LMB and RMB respectively for the first generation
- Clear the screen while drawing with CTRL+C
- Start the simulation with SPACE, or step through generations with ENTER
- Reset the simulation with CTRL+R

life -h:
```
Usage: life [-h] [-v] [-r] [-R <rule>] [-t <n>] [-u <n>] [-y]
    Options:
        -h          Print this help menu and exit.
        -r          Generate random starting generation on start-up.
        -R <rule>   Specify a Life-like rule. Game of Life rules are default.
                    Format: B<[0|1|...|8]>S<[0|1|...|8]>
                    Example: for GoL '-R B3S23', i.e. dead cell are born with 3 neighbors,
                    live cells survive with 2 or 3 neighbors.
        -t <n>      Specify the length of colored trails left by dead cells.
                    Set 0 to disable trails, default 6.
        -u <n>      Specify the updates per second. Unlimited by default.
        -v          Print version information and credits and exit.
        -y          Enable VSync.
```

# Compilation
Since I don't like the text editor in Visual Studio I chose to develop in VS Code instead. The compilation is not as straight-forward, as it requires an external compiler.

I used [mingw-w64](https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Compiling-on-Windows-with-Other-Compilers#compiling-with-mingw--msys2) to compile the app for Windows, and used the following command to do so:
```
$ g++ -fdiagnostics-color=always life.cpp about.cpp -o build\\release\\life.exe -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 -O3
```
For debugging replace `-O3` with `-g`

# Credits
Thanks OneLoneCoder, aka javidx9, and everyone else for developing the [olc::PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)! The license is included in the olcPixelGameEngine.h file.\
Here are some more links:\
https://OneLoneCoder.com \
[YouTube](https://youtube.com/javidx9)

Code for getopt.h/.c was taken from the Univerity of California and adapted to work on Windows, the full copyright notice is included in the source files.
