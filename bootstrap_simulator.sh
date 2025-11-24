#!/bin/bash

pacman -Syu --noconfirm
pacman -S mingw-w64-x86_64-toolchain --noconfirm

# Install pkg-config, cmake, and SDL2 for MinGW-w64
pacman -S mingw-w64-x86_64-pkg-config --noconfirm
pacman -S mingw-w64-x86_64-cmake --noconfirm
pacman -S mingw-w64-x86_64-SDL2 --noconfirm
echo "SDL2 and tools installed. Check with: pkg-config --libs sdl2 && cmake --version"
