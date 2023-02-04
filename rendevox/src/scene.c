#include "rendevox.h"

scene mainScene;

scene createScene(const char* type, const char* name) {
    scene tempScene;
    tempScene.type = type;
    tempScene.name = name;

    return tempScene;
}

void setMainScene(scene scene) {
    mainScene = scene;
}

scene* getMainScene() {
    return &mainScene;
}