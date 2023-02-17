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
- C standard libraries
- CMake
- Glfw
- Vulkan

## Features
- 3D rendering
- text rendering
- collision detection
- basic physics

## Template

```c
#include "rendevox.h"

int main(int argc, char *argv[]) {
    Window window = WindowCreate("OpenGL", "RVX", 1280, 720);
    WindowRun(&window);

    return 0;
}

void UserStart() {
    EntityBufferAddQuad("Quad1", "quad", (Vector2) {-1.0f, 0}, (Vector2) {0.2f, 0.4f});
    EntityBufferAddQuad("Quad2", "quad", (Vector2) {1.0f, 0}, (Vector2) {0.2f, 0.4f});
}

void UserUpdate(float delta) {
    //printf("%f\n", delta);
}
```

## How to run

1. Create directory `app` and create file `main.c` inside
2. Paste code from template
3. Create `CMake Application` configuration in CLion with `Target` = `All Targets` and `executable` = `rendevox`

Build script not working right now
``` shell
$ run.sh
```
