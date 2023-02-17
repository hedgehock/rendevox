typedef struct {
    char name[32];
    const char* type;

    Vector3 position;
    Vector3 rotation;
    mesh mesh;
} entity;