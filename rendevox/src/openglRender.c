#include "rendevox.h"

void openglRenderLoop() {
    userUpdate(0.0f);

    entity* entityBuffer = getEntityBuffer();
    unsigned int entityBufferSize = getEntityBufferSize();

    if (strcmp(getMainScene()->type, "2D") == 0) {
        for (int i = 0; i < entityBufferSize; i++) {
            entity currentEntity = entityBuffer[i];
        }
    }
}