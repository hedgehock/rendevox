void EntityBufferCreate();

entity* EntityBufferGet();
unsigned int EntityBufferGetSize();
void EntityBufferAddQuad(const char* name, const char* type, Vector2 position, Vector2 size);

void EntityBufferDestroy();