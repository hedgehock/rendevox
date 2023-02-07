#include "include/rendevox.h"

int main(int argc, char *argv[]) {
    window window;
    window.title = "RVX Window";
    window.renderType = "Vulkan";
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