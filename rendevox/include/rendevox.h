#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vulkan/vulkan.h>

// min and max functions are not in standard C library
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// TAU for delta time calculation
#define TAU (M_PI * 2.0)

// Rendevox headers
#include "window.h"
#include "user.h"
#include "vector2.h"
#include "vector3.h"
#include "color.h"
#include "triangle.h"
#include "matrix4.h"
#include "mesh.h"

// Entity declaration
typedef struct {
    char name[32];
    const char* type;

    vector3 position;
    vector3 rotation;
    mesh mesh;
} entity;

// EntityBuffer
void entityBufferCreate();

entity* entityBufferGet();
unsigned int entityBufferGetSize();
void entityBufferAddQuad(const char* name, const char* type, vector2 position, vector2 size);

void entityBufferDestroy();

// ---------
// Rendering
// ---------

//
// Opengl
//

void openglWindowRun(window window);

// Window
vector2 openglWindowGetSize();

// Render
void openglRenderCreate();
void loopOpenglRender();
void openglRenderDestroy();

//
// Vulkan
//

void runVulkanApp(window window);

// Vulkan main functions
void vulkanCreateWindow(window window);
void vulkanInit();
void vulkanMainLoop();
void vulkanCleanup();

// Vulkan initialisation functions
void vulkanCreateInstance();
void vulkanPickPhysicalDevice();

// Vulkan Pick Physical Device Functions
bool isDeviceSuitable(VkPhysicalDevice device);

// ---------
// Utilities
// ---------

// Sorting functions
void swap(triangle *a, triangle *b);
int partition(triangle arr[], int low, int high);
void quickSort(triangle arr[], int low, int high);
