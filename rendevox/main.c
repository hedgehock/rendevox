#include "rendevox.h"

int main(int argc, char *argv[]) {
    rvxCreateWindow("OpenGL", 1280, 720, "RVX Window", 0);

    return 0;
}

void userStart() {
    scene mainScene = createScene("2D", "Main scene");
    setMainScene(mainScene);

    mesh triangleMesh;
    triangleMesh.size = 9;
    triangleMesh.vertices = malloc(sizeof(float) * triangleMesh.size);
    //
    triangleMesh.vertices[0] = -0.5f;
    triangleMesh.vertices[1] = -0.5f;
    triangleMesh.vertices[2] = 0.0f;
    //
    triangleMesh.vertices[3] = 0.5f;
    triangleMesh.vertices[4] = -0.5f;
    triangleMesh.vertices[5] = 0.0f;
    //
    triangleMesh.vertices[6] = 0.5f;
    triangleMesh.vertices[7] = 0.5f;
    triangleMesh.vertices[8] = 0.0f;

    entity triangle;
    triangle.name = "Triangle1";
    triangle.position = (vector3){ 0, 0, 0};
    triangle.rotation = (vector3){ 0, 0, 0, 1};
    triangle.mesh = triangleMesh;

    addToEntityBuffer(triangle);

    mesh triangleMesh2;
    triangleMesh2.size = 9;
    triangleMesh2.vertices = malloc(sizeof(float) * triangleMesh2.size);
    //
    triangleMesh2.vertices[0] = -0.5f;
    triangleMesh2.vertices[1] = 0.5f;
    triangleMesh2.vertices[2] = 0.0f;
    //
    triangleMesh2.vertices[3] = -0.5f;
    triangleMesh2.vertices[4] = -0.5f;
    triangleMesh2.vertices[5] = 0.0f;
    //
    triangleMesh2.vertices[6] = 0.5f;
    triangleMesh2.vertices[7] = 0.5f;
    triangleMesh2.vertices[8] = 0.0f;

    entity triangle2;
    triangle2.name = "Triangle2";
    triangle2.position = (vector3){ 0, 0, 0};
    triangle2.rotation = (vector3){ 0, 0, 0, 1};
    triangle2.mesh = triangleMesh2;

    addToEntityBuffer(triangle2);
}

void userUpdate(float delta) {

}