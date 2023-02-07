typedef struct {
    char name[32];
    const char* type;

    vector3 position;
    vector3 rotation;
    mesh mesh;
} entity;