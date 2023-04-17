# MuVi

A simple application that visualizes the FFT of currently playing sounds in the system.
![Project logo, https://stablediffusionweb.com/#demo, prompt: "music visualiser logo '90 style neon"](logo.jpg)

## Description

This is a two-person project aimed to improve C++ coding skills, including Boost, OpenGL and parallel processing.

## Goals

The current goal is to provide a one-window app running on Windows that will attach to the default output device and provide some visualization of Fourier transformation.

## Dependencies

Clone repository with:

```console
git clone https://github.com/Kosciany/MuVi.git
git submodule init
git submodule update
```

### MSYS2 (recommended)

1. Download msys2-x86_64-*.exe installer from [msys2.org](https://msys2.org) and proceed with default installation. Add msys64/mingw64/bin to PATH environmental variable (`C:\msys64\mingw64\bin` by default)
2. Launch MSYS2 console (`C:\msys64\msys2.exe` by default)
3. Install dependencies

    ```console
    pacman -S mingw-w64-x86_64-toolchain msys2-w32api-headers msys2-w32api-runtime mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-boost mingw-w64-x86_64-spdlog
    ```

4. Navigate to repository folder (PowerShell/CMD should work)
5. Build & run

    ```console
    cmake -G ninja
    ninja
    audiotest.exe
    ```

### Boost standalone

1. Download Boost package [boost.org](https://www.boost.org/users/download/)
2. Extract the package and open the folder in a terminal
3. Run `.\bootstrap.bat`
4. Run `.\b2`
5. Copy the whole directory (e.g. `boost_1_81_0`) to `C:\Program Files\Boost`
