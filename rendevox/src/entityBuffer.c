#include "rendevox.h"

entity* entityBuffer;
unsigned int entityBufferSize = 0;

scene* mainScene;

void createEntityBuffer() {
    entityBuffer = malloc(sizeof(entity));

    mainScene = getMainScene();
}

void addToEntityBuffer(entity addEntity) {
    entityBufferSize += 1;
    entityBuffer = realloc(entityBuffer, sizeof(entity) * entityBufferSize);
    entityBuffer[entityBufferSize - 1] = addEntity;
}

void loopEntityBuffer(const char* renderType) {
    // Call user's update function
    userUpdate(0.0f);

    // Main Loop
    if (strcmp(mainScene->type, "3D") == 0) {
        for (int i = 0; i < entityBufferSize; i++) {
            entity currentEntity = entityBuffer[i];
        }
    }
}