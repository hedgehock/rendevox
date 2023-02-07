void entityBufferCreate();

entity* entityBufferGet();
unsigned int entityBufferGetSize();
void entityBufferAddQuad(const char* name, const char* type, vector2 position, vector2 size);

void entityBufferDestroy();