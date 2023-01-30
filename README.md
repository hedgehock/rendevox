# Rendevox

## Dependencies
Install script for Arch Linux (xorg display server)
``` shell
$ install-arch-dependencies.sh
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

## msys2 mingw64 dependencies
- mingw-w64-x86_64-SDL2_ttf
- mingw-w64-x86_64-glfw
- mingw-w64-x86_64-vulkan-devel
- mingw-w64-x86_64-kf5
- mingw-w64-x86_64-toolchain

## Example code
```c
#include "rendevox.h"

int main() {
	rvxCreatewindow("SDL2", 1280, 720, "RVX Window", 0);
}

void start() {
	entity cube = { 0 };
	cube.name("Cube1");
	cube.position = (vector3){ 0, 0, 0 };
	cube.rotation = (vector3){ 0, 0, 0, 0 };
	cube.mesh = loadMeshFromFile("model.obj");
	addToEntityBuffer(cube);
}

void update(int deltaSeconds) {
	if(isKeyPressed(KEYBOARD_W)) {
		object cube = findEntity("Cube1");
		cube.position = vector3Add(cube.position, (vector3){ 0, 0, 1 });
	}
}
```

## How to run
``` shell
$ run.sh
```
