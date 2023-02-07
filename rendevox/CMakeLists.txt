cmake_minimum_required(VERSION 3.23)
project(rendevox C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-O3")

include_directories(src)
include_directories(include)

if (APPLE)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
    link_libraries(glfw vulkan m)
elseif(UNIX)
    link_libraries(glfw vulkan m)
elseif(WIN32)
    find_package(Vulkan REQUIRED)

    include_directories(/c/msys64/mingw64/include)
    link_directories(/c/msys64/mingw64/lib)
    link_libraries(mingw32 Vulkan::Vulkan glfw3 glu32 opengl32 gdi32 m)
endif()

file(GLOB SRC src/*.c)
add_executable(rendevox)

target_sources(rendevox PRIVATE main.c ${SRC})
