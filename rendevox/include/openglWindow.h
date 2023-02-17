#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

typedef struct {
    Window *window;

    const char* vertexShaderSource;
    const char* fragmentShaderSource;

    GLFWwindow* glfwWindow;
    unsigned int shaderProgram;

    bool debug;
} OpenglWindow;

OpenglWindow OpenglWindowCreate(Window *window, const char* vertexShaderSource, const char* fragmentShaderSource, bool debug);

void OpenglWindowRun(OpenglWindow *openglWindow);
void OpenglWindowInit(OpenglWindow *openglWindow);
void OpenglWindowCompileShaders(OpenglWindow *openglWindow);
void OpenglWindowProcessInput(GLFWwindow *window);
void OpenglWindowLoop(OpenglWindow *openglWindow);
void OpenglWindowDestroy(OpenglWindow *openglWindow);

#endif