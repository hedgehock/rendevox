#include "rendevox.h"

void addTriangleToMesh(mesh *m, triangle t) {
    m->t = realloc(m->t, sizeof(triangle) * (m->size + 1));
    m->t[m->size] = t;
    m->size++;
}

void loadMeshFromFile(mesh *m, const char *path) {
    m->size = 0;
    m->t = malloc(sizeof(triangle));;

    FILE *file;
    char line[32];

    file = fopen(path, "r");
    if (file == NULL) {
        printf("Can't load fire from desired path");
        exit(EXIT_FAILURE);
    }

    char vCount = 0, fCount = 0;

    vector3 *tempVectors = malloc(sizeof(vector3));
    int tempVectorsSize = 0;
    triangle tempTriangle;

    while (fscanf(file, " %31s", line) == 1) {
        if (vCount > 0) {
            if (vCount == 3) tempVectors[tempVectorsSize].x = atof(line);
            if (vCount == 2) tempVectors[tempVectorsSize].y = atof(line);
            if (vCount == 1) {
                // Reallocate +2 vectors to have space for the next
                tempVectors = realloc(tempVectors, sizeof(vector3) * (tempVectorsSize + 2));

                tempVectors[tempVectorsSize].z = atof(line);

                tempVectorsSize++;
            }

            // Decrease vector count to append next property
            vCount--;
        }
        else if (fCount > 0) {
            if (fCount == 3) tempTriangle.p[0] = tempVectors[atoi(line)];
            if (fCount == 2) tempTriangle.p[1] = tempVectors[atoi(line)];
            if (fCount == 1) {
                tempTriangle.p[2] = tempVectors[atoi(line)];

                // Set triangle w properties
                tempTriangle.p[0].w = 1.0f;
                tempTriangle.p[1].w = 1.0f;
                tempTriangle.p[2].w = 1.0f;

                // Append triangle to mesh
                addTriangleToMesh(m, tempTriangle);
            }

            // Decrease faces count to append next point of the triangle
            fCount--;
        }
        else {
            if (line[0] == 'v') {
                vCount = 3;
            }
            else if (line[0] == 'f') {
                fCount = 3;
            }
        }
    }

    // Free memory
    fclose(file);
    free(tempVectors);
}