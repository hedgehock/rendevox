#include <rendevox.h>

entity* entityBuffer;
unsigned int entityBufferSize = 0;

void EntityBufferCreate() {
    entityBuffer = malloc(sizeof(entity));
}

void EntityBufferDestroy() {
    free(entityBuffer);
}

entity* EntityBufferGet() {
    return entityBuffer;
}

unsigned int EntityBufferGetSize() {
    return entityBufferSize;
}

void entityBufferAdd(entity newEntity) {
    entityBufferSize++;
    entityBuffer = realloc(entityBuffer, sizeof(entity) * entityBufferSize);
    entityBuffer[entityBufferSize - 1] = newEntity;
}

void EntityBufferAddQuad(const char* name, const char* type, Vector2 position, Vector2 size) {
    mesh quadMesh;
    quadMesh.vertices = malloc(sizeof(float) * 18);
    //
    quadMesh.vertices[0] = -0.5f * size.x + position.x;
    quadMesh.vertices[1] = -0.5f * size.y + position.y;
    quadMesh.vertices[2] = 0.0f;
    //
    quadMesh.vertices[3] = 0.5f * size.x + position.x;
    quadMesh.vertices[4] = -0.5f * size.y + position.y;
    quadMesh.vertices[5] = 0.0f;
    //
    quadMesh.vertices[6] = 0.5f * size.x + position.x;
    quadMesh.vertices[7] = 0.5f * size.y + position.y;
    quadMesh.vertices[8] = 0.0f;

    //
    quadMesh.vertices[9] = -0.5f * size.x + position.x;
    quadMesh.vertices[10] = 0.5f * size.y + position.y;
    quadMesh.vertices[11] = 0.0f;
    //
    quadMesh.vertices[12] = -0.5f * size.x + position.x;
    quadMesh.vertices[13] = -0.5f * size.y + position.y;
    quadMesh.vertices[14] = 0.0f;
    //
    quadMesh.vertices[15] = 0.5f * size.x + position.x;
    quadMesh.vertices[16] = 0.5f * size.y + position.y;
    quadMesh.vertices[17] = 0.0f;

    entity quad = { 0 };
    strcat(quad.name, name);
    quad.type = type;
    quad.mesh = quadMesh;

    entityBufferAdd(quad);
}
