cmake_minimum_required(VERSION 3.24)
project(rendevox C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-O3")

include_directories(src)

if (APPLE)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
    link_libraries(glfw vulkan SDL2 SDL2_ttf m)
elseif(UNIX)
    link_libraries(glfw vulkan SDL2 SDL2_ttf m)
elseif(WIN32)
    find_package(Vulkan REQUIRED)

    include_directories(/c/msys64/mingw64/include)
    link_directories(/c/msys64/mingw64/lib)
    link_libraries(mingw32 Vulkan::Vulkan glfw3 glu32 opengl32 gdi32 SDL2Main SDL2 SDL2_ttf m)
endif()

file(GLOB SRC src/*.c)
add_executable(rendevox)

target_sources(rendevox PRIVATE main.c ${SRC})
