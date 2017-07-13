# Desktop Streamer (Windows version)

## C utility to start a desktop stream with VLC and broadcast the fact over TCP

Made with Raspberry Pi integration in mind, default configuration is compatible with Pi Zero W.

This is my first C project. It uses WinAPI, OpenMP and cmake. I wrote a helper library while working on this project, you can find it in src/utils.

# Installing

Install VLC. Then download this project's [binary files](https://github.com/pzmarzly/DesktopStreamerWin/releases/latest) or [build them](#building). Place the files anywhere, just make sure to invoke the programs with the same working directory, as it is the place where the config will be stored.

# Usage

First time you run `start.exe` or `stop.exe`, settings file will be generated and nothing more will be done.

Run `start.exe` to start streaming and notify local devices. Check `start.exe -h` for more information about manual device selection. Run `stop.exe` to stop local VLC.

On Raspberry Pi, use a script that will catch the password and run (no Xserver required):

    omxplayer --live http://....:.../streamer.avi --fps ..

I will provide such script soon (hopefully).

# Building

Requirements:
- TDM-GCC
- CMake

Recommended:
- ninja build system

Add all of them to PATH, then call:

    mkdir build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release [-DUSE_MESSAGEBOX_GUI if you want GUI]
    ninja

If you don't use ninja, adjust your commands.

I've included Visual Studio Code settings for quick building with Ctrl-Shift-B.

# Limitations

- this program will behave unexpectedly if the config file is corrupt/incorrect
- only IPv4 addresses are supported
