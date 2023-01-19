# Rendevox

## TODO
- [ ] add references to functions

## Dependencies
- C99 compiler
- C standard library
- SDL2

## Features
- 3D rendering
- text rendering
- collision detection
- basic physics

## Code
```c
#include "rendevox.h"

int main() {
	createwindow(1280, 720);
}

void start() {
	Object cube = { 0 };
	cube.name("Cube1");
	cube.position = (Vector3){ 0, 0, 0 };
	cube.mesh = loadmesh("model.obj");
	addtobuffer(cube);
}

void update(int delta) {
	if(iskeypressed(KEYBOARD_W)) {
		Object cube = findobject("Cube1");
		cube.position = vector3add(cube.position, (Vector3){ 0, 0, 1 });
	}
}
```

## How to run

### linux
```
$ run-linux.sh
```
