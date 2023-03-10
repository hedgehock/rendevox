#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// min and max functions are not in standard C library
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// TAU for delta time calculation
#define TAU (M_PI * 2.0)

// Rendevox headers
#include "user.h"

#include "window.h"

#include "vector2.h"
#include "vector3.h"
#include "color.h"
#include "triangle.h"
#include "matrix4.h"
#include "mesh.h"
#include "entity.h"

#include "mathematicalOperations.h"
#include "sorting.h"
#include "entityBuffer.h"

#include "openglWindow.h"
#include "openglRender.h"

#include "vulkanWindow.h"
