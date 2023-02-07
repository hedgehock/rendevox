# Rendevox

## Dependencies
#### Install script for Arch Linux (xorg display server)
``` shell
$ install-arch-dependencies.sh
```

#### Install for Windows via [MSYS2](https://repo.msys2.org/distrib/x86_64/) latest version
```shell
$ pacman -S mingw-w64-x86_64-toolchain
$ pacman -S mingw-w64-x86_64-cmake
$ pacman -S mingw-w64-x86_64-SDL2
$ pacman -S mingw-w64-x86_64-SDL2_ttf
$ pacman -S mingw-w64-x86_64-glfw
$ pacman -S mingw-w64-x86_64-vulkan-devel
```

- C99 compiler
- C standard library
- CMake
- SDL2 and SDL2_ttf
- Glfw
- Vulkan

## Features
- 3D rendering
- text rendering
- collision detection
- basic physics

## How to run
``` shell
$ run.sh
```
