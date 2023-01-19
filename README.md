# Rendevox

## Dependencies
- C99 compiler
- C standard library
- SDL2

## Features
- 3D rendering
- text rendering
- collision detection
- basic physics

## Structures
- ### Vector3
	- `float x`
	- `float y`
	- `float z`
	- `float w`
- ### Matrix4
	- `float m[4][4]`
- ### Color
	- `signed char r`
	- `signed char g`
	- `signed char b`
- ### Triangle
	- `Vector3 points[3]`
	- `Color color`
- ### Mesh
  - `unsigned int size`
  - `Triangle *triangles`
- ### Object
	- `const char* name`
	- `Vector3 position`
	- `Vector3 rotation`
	- `Mesh mesh`
- ### Font
  - `TTF_Font *ttf_font`

## Code
```c
#include "rendevox.h"

int main() {
	createwindow(1920, 1080);
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
