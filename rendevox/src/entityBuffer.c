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

void addQuadToEntityBuffer(const char* name, vector2 position, vector2 size) {
    vector2 windowSize = getWindowSizeOpenglWindow();
    float windowSizeX = windowSize.y / 1000.0f;
    float windowSizeY = windowSize.x / 1000.0f;

    mesh triangleMesh;
    triangleMesh.size = 9;
    triangleMesh.vertices = malloc(sizeof(float) * triangleMesh.size);
    //
    triangleMesh.vertices[0] = (-0.5f * size.x + position.x) * windowSizeX;
    triangleMesh.vertices[1] = (-0.5f * size.y + position.y) * windowSizeY;
    triangleMesh.vertices[2] = 0.0f;
    //
    triangleMesh.vertices[3] = (0.5f * size.x + position.x) * windowSizeX;
    triangleMesh.vertices[4] = (-0.5f * size.y + position.y) * windowSizeY;
    triangleMesh.vertices[5] = 0.0f;
    //
    triangleMesh.vertices[6] = (0.5f * size.x + position.x) * windowSizeX;
    triangleMesh.vertices[7] = (0.5f * size.y + position.y) * windowSizeY;
    triangleMesh.vertices[8] = 0.0f;

    entity triangle = { 0 };
    strcat(triangle.name, name);
    strcat(triangle.name, "t1");
    triangle.position = (vector3){ 0, 0, 0 };
    triangle.rotation = (vector3){ 0, 0, 0, 1 };
    triangle.mesh = triangleMesh;

    addToEntityBuffer(triangle);

    mesh triangleMesh2;
    triangleMesh2.size = 9;
    triangleMesh2.vertices = malloc(sizeof(float) * triangleMesh2.size);
    //
    triangleMesh2.vertices[0] = (-0.5f * size.x + position.x) * windowSizeX;
    triangleMesh2.vertices[1] = (0.5f * size.y + position.y) * windowSizeY;
    triangleMesh2.vertices[2] = 0.0f;
    //
    triangleMesh2.vertices[3] = (-0.5f * size.x + position.x) * windowSizeX;
    triangleMesh2.vertices[4] = (-0.5f * size.y + position.y) * windowSizeY;
    triangleMesh2.vertices[5] = 0.0f;
    //
    triangleMesh2.vertices[6] = (0.5f * size.x + position.x) * windowSizeX;
    triangleMesh2.vertices[7] = (0.5f * size.y + position.y) * windowSizeY;
    triangleMesh2.vertices[8] = 0.0f;

    entity triangle2 = { 0 };
    strcat(triangle2.name, name);
    strcat(triangle2.name, "t2");
    triangle2.position = (vector3){ 0, 0, 0};
    triangle2.rotation = (vector3){ 0, 0, 0, 1};
    triangle2.mesh = triangleMesh2;

    addToEntityBuffer(triangle2);
}
