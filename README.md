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

## Example code
```c
#include "rendevox.h"

int main() {
	rvxCreatewindow("SDL2", 1280, 720, "RVX Window", 0);
}

void start() {
	Scene scene = createScene("3D", "Main scene");
	setMainScene(scene);

	Entity cube = { 0 };
	cube.name("Cube1");
	cube.position = (vector3){ 0, 0, 0 };
	cube.rotation = (vector3){ 0, 0, 0, 0 };
	cube.mesh = loadMeshFromFile("model.obj");
	addToEntityBuffer(cube);
}

void update(int deltaSeconds) {
	if(isKeyPressed(KEYBOARD_W)) {
		Entity cube = findEntity("Cube1");
		cube.position = vector3Add(cube.position, (vector3){ 0, 0, 1 });
	}
}
```

## How to run
``` shell
$ run.sh
```
