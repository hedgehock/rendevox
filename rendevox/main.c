#include "rendevox.h"

int main(int argc, char *argv[]) {
    rvxCreateWindow("OpenGL", 1280, 720, "RVX Window", 0);

    return 0;
}

void userStart() {
    addQuadToEntityBuffer("Quad1", (vector2){ -0.5f, 0 }, (vector2){ 0.2f, 0.2f });
    addQuadToEntityBuffer("Quad2", (vector2){ 0.5f, 0 }, (vector2){ 0.2f, 0.2f });
}

void userUpdate(float delta) {
    //printf("%f\n", delta);
}