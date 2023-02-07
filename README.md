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

## Template

```c
#include "include/rendevox.h"

int main(int argc, char *argv[]) {
    window window;
    window.title = "RVX Window";
    window.renderType = "OpenGL";
    window.width = 1280;
    window.height = 720;
    windowCreate(&window);

    return 0;
}

void userStart() {
    entityBufferAddQuad("Quad1", "quad", (vector2){ -1.0f, 0 }, (vector2){ 0.2f, 0.4f });
    entityBufferAddQuad("Quad2", "quad", (vector2){ 1.0f, 0 }, (vector2){ 0.2f, 0.4f });
}

void userUpdate(float delta) {
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
