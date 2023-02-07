#include "rendevox.h"

int main(int argc, char *argv[]) {
    rvxCreateWindow("OpenGL", 1280, 720, "RVX Window", 0);

    return 0;
}

void userStart() {
    addQuadToEntityBuffer("Quad1", "quad", (vector2){ -1.0f, 0 }, (vector2){ 0.2f, 0.4f });
    addQuadToEntityBuffer("Quad2", "quad", (vector2){ 1.0f, 0 }, (vector2){ 0.2f, 0.4f });
}

void userUpdate(float delta) {
    //printf("%f\n", delta);
}