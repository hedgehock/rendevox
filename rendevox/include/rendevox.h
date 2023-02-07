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
#include "entity.h"
#include "entityBuffer.h"
#include "openglWindow.h"
#include "sorting.h"
