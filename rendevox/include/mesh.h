typedef struct {
    int size;
    triangle *t;
    float* vertices;
} mesh;

mesh loadMeshFromFile(const char* path);