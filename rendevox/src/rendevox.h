#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vulkan/vulkan.h>

// Rendevox
void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen);
void userStart();
void userUpdate(float delta);

// ----------
// Data types
// ----------

// min and max functions are not in standard C library
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// Vector2 declaration
typedef struct {
    float x;
    float y;
} vector2;

// Vector3 declaration
typedef struct {
    float x;
    float y;
    float z;
    float w;
} vector3;

// Vector3 functions
vector3 vector3Add(vector3 *v1, vector3 *v2);
vector3 vector3Sub(vector3 *v1, vector3 *v2);
vector3 vector3Mul(vector3 *v1, float amount);
vector3 vector3Div(vector3 *v1, float amount);
float vector3DotProduct(vector3 *v1, vector3 *v2);
float vector3Length(vector3 *v);
vector3 vector3Normalise(vector3 *v);
vector3 vector3CrossProduct(vector3 *v1, vector3 *v2);
vector3 vector3IntersectPlane(vector3 *planeP, vector3 *planeN, vector3 *lineStart, vector3 *lineEnd);

// Color declaration
typedef struct {
    signed char r;
    signed char g;
    signed char b;
    signed char a;
} color;

// Triangle declaration
typedef struct {
    vector3 p[3];
    color c;
} triangle;

// Matrix4 declaration
typedef struct {
    float m[4][4];
} matrix4;

// Vector3 function that requires matrix4
vector3 matrix4MultiplyVector3(matrix4 *m, vector3 *i);

// Matrix4 functions
matrix4 matrix4MakeIdentity();
matrix4 matrix4MakeRotationX(float angleRad);
matrix4 matrix4MakeRotationY(float angleRad);
matrix4 matrix4MakeRotationZ(float angleRad);
matrix4 matrix4MakeTranslation(float x, float y, float z);
matrix4 matrix4MakeProjection(float fovDegrees, float aspectRatio, float near, float far);
matrix4 matrix4MultiplyMatrix4(matrix4 *m1, matrix4 *m2);
matrix4 matrix4PointAt(vector3 *pos, vector3 *target, vector3 *up);
matrix4 matrix4QuickInverse(matrix4 *m);

// Mesh declaration
typedef struct {
    int size;
    triangle *t;
    float* vertices;
} mesh;

// Mesh functions
mesh loadMeshFromFile(const char* path);

// Font declaration
typedef struct {
    TTF_Font *ttfFont;
} font;

// Font functions
font sdlLoadFont(const char* path);

// Window declaration
typedef struct {
    const char* renderType;
    const char* title;
    int width;
    int height;

    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
} window;

// Entity declaration
typedef struct {
    const char* name;
    vector3 position;
    vector3 rotation;
    mesh mesh;
} entity;

// Entity functions
void createEntityBuffer();
void loopEntityBuffer(const char* renderType);
void addToEntityBuffer(entity addEntity);

// Scene declaration
typedef struct {
    const char* type;
    const char* name;
} scene;

// Scene functions
scene createScene(const char* type, const char* name);
void setMainScene(scene scene);
scene* getMainScene();

// ---------
// Rendering
// ---------

//
// SDL2
//

// SDL2 window
void runSDLApp(window window);

// SDL 2 drawing
void drawTriangle(SDL_Renderer *renderer, vector2 v1, vector2 v2, vector2 v3, color color);
void drawText(SDL_Renderer *renderer, int x, int y, char *text, font font);

//
// Opengl
//

void runOpenglApp(window window);

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
