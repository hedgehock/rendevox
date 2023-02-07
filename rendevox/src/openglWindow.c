#include <rendevox.h>

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 vertexColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vertexColor;\n"
                                   "}\n\0";

vector2 windowSize = (vector2){ 0, 0 };

GLFWwindow* glfwWindow;

unsigned int shaderProgram;

void openglWindowProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void openglWindowFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowSize.x = (float)width;
    windowSize.y = (float)height;
}

vector2 openglWindowGetSize() {
    return windowSize;
}

void openglWindowCreate(window window)
{
    windowSize.x = (float)window.width;
    windowSize.y = (float)window.height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (glfwWindow == NULL)
    {
        printf("Cannot create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, openglWindowFramebufferSizeCallback);

    glfwSetWindowAttrib(glfwWindow, GLFW_RESIZABLE, GL_FALSE);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Cannot load GLAD");
        exit(EXIT_FAILURE);
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed");
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed");
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader program linking failed");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void openglWindowLoop(window window) {
    while (!glfwWindowShouldClose(glfwWindow)) {
        // Handle Input
        openglWindowProcessInput(glfwWindow);

        // Render Start
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        // Render Loop
        loopOpenglRender();

        // Render End
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }
}

void openglWindowDestroy() {
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

void openglWindowRun(window window) {
    openglWindowCreate(window);
    entityBufferCreate();
    openglRenderCreate();

    userStart();

    openglWindowLoop(window);

    openglRenderDestroy();
    entityBufferDestroy();
    openglWindowDestroy();
}