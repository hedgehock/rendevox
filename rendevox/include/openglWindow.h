typedef struct {
    const char* vertexShaderSource;
    const char* fragmentShaderSource;

    const char* title;
    vector2 windowSize;

    GLFWwindow* glfwWindow;
    unsigned int shaderProgram;
} openglWindow;

void openglWindowRun(window window);
vector2 openglWindowGetSize();