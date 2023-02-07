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

void addToEntityBuffer(entity newEntity) {
    entityBufferSize++;
    entityBuffer = realloc(entityBuffer, sizeof(entity) * entityBufferSize);
    entityBuffer[entityBufferSize - 1] = newEntity;
}

void addQuadToEntityBuffer(const char* name, const char* type, vector2 position, vector2 size) {
    vector2 windowSize = getWindowSizeOpenglWindow();
    float windowSizeX = windowSize.y / 1000.0f;
    float windowSizeY = windowSize.x / 1000.0f;

    mesh quadMesh;
    quadMesh.size = 18;
    quadMesh.vertices = malloc(sizeof(float) * quadMesh.size);
    //
    quadMesh.vertices[0] = (-0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[1] = (-0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[2] = 0.0f;
    //
    quadMesh.vertices[3] = (0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[4] = (-0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[5] = 0.0f;
    //
    quadMesh.vertices[6] = (0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[7] = (0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[8] = 0.0f;

    //
    quadMesh.vertices[9] = (-0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[10] = (0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[11] = 0.0f;
    //
    quadMesh.vertices[12] = (-0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[13] = (-0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[14] = 0.0f;
    //
    quadMesh.vertices[15] = (0.5f * size.x + position.x) * windowSizeX;
    quadMesh.vertices[16] = (0.5f * size.y + position.y) * windowSizeY;
    quadMesh.vertices[17] = 0.0f;

    entity quad = { 0 };
    strcat(quad.name, name);
    quad.type = type;
    quad.position = (vector3){ 0, 0, 0 };
    quad.rotation = (vector3){ 0, 0, 0, 1 };
    quad.mesh = quadMesh;

    addToEntityBuffer(quad);
}
