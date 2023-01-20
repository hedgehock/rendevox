# Rendevox

## TODO
- [ ] add references to functions

## Dependencies
- C99 compiler
- C standard library
- SDL2 and SDL2_ttf

## Features
- 3D rendering
- text rendering
- collision detection
- basic physics

## Example code
```c
#include "rendevox.h"

int main() {
	createwindow(1280, 720, "rendevox window");
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

### linux
```
$ run-linux.sh
```

### macos
```
$ run-macos.sh
```
