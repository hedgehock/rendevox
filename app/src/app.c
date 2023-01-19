#include "rendevox.h"

int main() {
	createWindow(1280, 720, "SDLWINDOW");
	
	return 0;
}

void start() {
	entity e = { 0 };
	e.name = "Test1";
	e.position = (vector3){ 0, 0, 0 };
	e.rotation = (vector3){ 0, 0, 0, 0 };
	addToEntityBuffer(e);
}

void update(int deltaSeconds) {

}
