#include "../include/rendevox.h"

mesh loadMeshFromFile(const char* path) {
    FILE *f;

    f = fopen(path, "r");

    if (f == NULL) {
        printf("Can't load fire from desired path");
        exit(EXIT_FAILURE);
    }

    char lineBuff[64];

    char vertexCount = 0;
    char faceCount = 0;

    vector3 *vBuff = malloc(sizeof(vector3));
    unsigned int vBuffSize = 0;

    mesh tempMesh;
    tempMesh.size = 0;
    tempMesh.t = malloc(sizeof(triangle));

    while (fscanf(f, " %63s", lineBuff) == 1) {
        if (vertexCount > 0) {
            if (vertexCount == 3) {
                vBuff[vBuffSize].x = atof(lineBuff);
            }
            else if (vertexCount == 2) {
                vBuff[vBuffSize].y = atof(lineBuff);
            }
            else if (vertexCount == 1) {
                vBuff[vBuffSize].z = atof(lineBuff);

                vBuffSize += 1;
                vBuff = realloc(vBuff, sizeof(vector3) * (vBuffSize + 1));
            }

            vertexCount -= 1;
        }
        if (faceCount > 0) {
            if (faceCount == 3) {
                tempMesh.t[tempMesh.size].p[0] = vBuff[atoi(lineBuff) - 1];
            }
            else if (faceCount == 2) {
                tempMesh.t[tempMesh.size].p[1] = vBuff[atoi(lineBuff) - 1];
            }
            else if (faceCount == 1) {
                tempMesh.t[tempMesh.size].p[2] = vBuff[atoi(lineBuff) - 1];

                tempMesh.t[tempMesh.size].p[0].w = 1.0f;
                tempMesh.t[tempMesh.size].p[1].w = 1.0f;
                tempMesh.t[tempMesh.size].p[2].w = 1.0f;

                tempMesh.size += 1;
                tempMesh.t = realloc(tempMesh.t, sizeof(triangle) * (tempMesh.size + 1));
            }

            faceCount -= 1;
        }
        else if (strcmp(lineBuff, "v") == 0) {
            vertexCount = 3;
        }
        else if (strcmp(lineBuff, "f") == 0) {
            faceCount = 3;
        }
        else {
            printf("%s ", lineBuff);
        }
    }

    for (int i = 0; i < vBuffSize; i++) {
        printf("\nvector3 | %f %f %f", vBuff[i].x, vBuff[i].y, vBuff[i].z);
    }

    for (int i = 0; i < tempMesh.size; i++) {
        printf("\n-- Triangle --");
        printf("\np1: %f %f %f", tempMesh.t[i].p[0].x, tempMesh.t[i].p[0].y, tempMesh.t[i].p[0].z);
        printf("\np2: %f %f %f", tempMesh.t[i].p[1].x, tempMesh.t[i].p[1].y, tempMesh.t[i].p[1].z);
        printf("\np3: %f %f %f", tempMesh.t[i].p[2].x, tempMesh.t[i].p[2].y, tempMesh.t[i].p[2].z);
    }

    free(vBuff);
    fclose(f);

    return tempMesh;
}