#include "rendevox.h"

entity* entityBuffer;
unsigned int entityBufferSize = 0;


void createEntityBuffer() {
    entityBuffer = malloc(sizeof(entity));
}

entity* getEntityBuffer() {
    return entityBuffer;
}

unsigned int getEntityBufferSize() {
    return entityBufferSize;
}

void addToEntityBuffer(entity addEntity) {
    entityBufferSize += 1;
    entityBuffer = realloc(entityBuffer, sizeof(entity) * entityBufferSize);
    entityBuffer[entityBufferSize - 1] = addEntity;
}
