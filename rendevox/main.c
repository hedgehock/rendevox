#include "rendevox.h"

int main(int argc, char *argv[]) {
    rvxCreateWindow("OpenGL", 1280, 720, "RVX Window", 0);

    return 0;
}

void userStart() {
    scene mainScene = createScene("3D", "Main scene");
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
    triangleMesh.vertices[6] = 0.0f;
    triangleMesh.vertices[7] = 0.5f;
    triangleMesh.vertices[8] = 0.0f;

    entity triangle;
    triangle.name = "Triangle1";
    triangle.position = (vector3){ 0, 0, 0};
    triangle.rotation = (vector3){ 0, 0, 0, 1};
    triangle.mesh = triangleMesh;

    addToEntityBuffer(triangle);
}

void userUpdate(float delta) {

}