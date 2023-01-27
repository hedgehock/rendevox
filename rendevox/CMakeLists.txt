cmake_minimum_required(VERSION 3.20)
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
endif()

file(GLOB SRC src/*.c)
add_executable(rendevox ${SRC})