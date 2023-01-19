#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Macros
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// User functions
int createWindow(int width, int height, const char *title);
void start();
void update(int deltaSeconds);
int getFps();

// Vector2
typedef struct {
	float x;
	float y;
} vector2;

// Vector3
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

// Color
typedef struct {
	signed char r;
	signed char g;
	signed char b;
	signed char a;
} color;

// Triangle
typedef struct {
	vector3 points[3];
	color color;
} triangle;

// Matrix4
typedef struct {
	float matrix[4][4];	
} matrix4;

// Matrix4 functions
vector3 matrixMultiplyVector(matrix4 *m, vector3 *v);
matrix4 matrixMakeIdentity();
matrix4 matrixMakeRotationX(float fAngleRad);
matrix4 matrixMakeRotationY(float fAngleRad);
matrix4 matrixMakeRotationZ(float fAngleRad);
matrix4 matrixMakeTranslation(float x, float y, float z);
matrix4 matrixMakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
matrix4 matrixMultiplyMatrix(matrix4 *m1, matrix4 *m2);
matrix4 matrixPointAt(vector3 *pos, vector3 *target, vector3 *up);
matrix4 matrixQuickInverse(matrix4 *m);

// Mesh
typedef struct {
	unsigned int size;
	triangle *t;
} mesh;

typedef struct {
	const char* name;
	vector3 position;
	vector3 rotation;
	mesh mesh;
} entity;

mesh loadMeshFromFile(const char *path);

// Font
typedef struct {
	TTF_Font *ttfFont;
} font;

font loadFont(const char *path);

// Camera
float dist(vector3 planeN, vector3 planeP, vector3 *p);
int triangleClipAgainstPlane(vector3 planeP, vector3 planeN, triangle *inTri, triangle *outTri1, triangle *outTri2);

// Sorting
void swap(triangle *a, triangle *b);
int partition(triangle arr[], int low, int high);
void quickSort(triangle arr[], int low, int high);

// Drawing
void drawTriangle(SDL_Renderer *renderer, vector2 v1, vector2 v2, vector2 v3, color color);
void drawText(SDL_Renderer *renderer, int x, int y, char *text, font font);

// Render
int createRender(SDL_Window *sdlWindow);
void addToEntityBuffer(entity e);
void destroyRender();
void render(int deltaSeconds);
