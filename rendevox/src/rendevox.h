#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Rendevox
void rvxCreateWindow(const char* renderType, int width, int height, const char* title, char fullscreen);

void runVulkanApp();

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

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

vector3 vector_add(vector3 *v1, vector3 *v2);
vector3 vector_sub(vector3 *v1, vector3 *v2);
vector3 vector_mul(vector3 *v1, float k);
vector3 vector_div(vector3 *v1, float k);
float vector_dot_product(vector3 *v1, vector3 *v2);
float vector_length(vector3 *v);
vector3 vector_normalise(vector3 *v);
vector3 vector_cross_product(vector3 *v1, vector3 *v2);
vector3 vector_intersect_plane(vector3 *plane_p, vector3 *plane_n, vector3 *line_start, vector3 *line_end);

// Color
typedef struct {
    signed char r;
    signed char g;
    signed char b;
    signed char a;
} color;

// Triangle
typedef struct {
    vector3 p[3];
    color c;
} triangle;

// Matrix4
typedef struct {
    float m[4][4];
} matrix4;

void init_matrix(matrix4* m);
vector3 matrix_multiply_vector(matrix4 *m, vector3 *i);
matrix4 matrix_make_identity();
matrix4 matrix_make_rotationx(float f_angle_rad);
matrix4 matrix_make_rotationy(float f_angle_rad);
matrix4 matrix_make_rotationz(float f_angle_rad);
matrix4 matrix_make_translation(float x, float y, float z);
matrix4 matrix_make_projection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
matrix4 matrix_multiply_matrix(matrix4 *m1, matrix4 *m2);
matrix4 matrix_point_at(vector3 *pos, vector3 *target, vector3 *up);
matrix4 matrix_quick_inverse(matrix4 *m);

// Mesh
typedef struct {
    int size;
    triangle *t;
} mesh;

void init_mesh(mesh *mesh);
int load_file(mesh *mesh, const char *path);

// Font
typedef struct {
    TTF_Font *ttfFont;
} font;

font loadFont(const char* path);

// Window
typedef struct {
    const char* title;
    int width;
    int height;

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
} window;

void createWindow(window *window, const char* renderType, int width, int height, const char *title);
void destroyWindow(window *window);

// Camera
float dist(vector3 plane_n, vector3 plane_p, vector3 *p);
int Triangle_ClipAgainstPlane(vector3 plane_p, vector3 plane_n, triangle *in_tri, triangle *out_tri1, triangle *out_tri2);

// Sorting
void swap(triangle *a, triangle *b);
int partition(triangle arr[], int low, int high);
void quickSort(triangle arr[], int low, int high);

// Drawing
void draw_triangle(SDL_Renderer *renderer, vector2 v1, vector2 v2, vector2 v3, color color);
void drawText(SDL_Renderer *renderer, int x, int y, char *text, font font);

// Render
int init_render(window window);
void render(window window, int delta);
