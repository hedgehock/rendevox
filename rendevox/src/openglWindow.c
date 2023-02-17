#include <rendevox.h>

OpenglWindow OpenglWindowCreate(Window *window, const char* vertexShaderSource, const char* fragmentShaderSource, bool debug) {
    OpenglWindow result;
    result.window = window;
    result.vertexShaderSource = vertexShaderSource;
    result.fragmentShaderSource = fragmentShaderSource;
    result.debug = debug;
    return result;
}

void OpenglWindowRun(OpenglWindow *openglWindow) {
    OpenglWindowInit(openglWindow);
    OpenglWindowCompileShaders(openglWindow);
    EntityBufferCreate();

    UserStart();

    OpenglWindowLoop(openglWindow);

    EntityBufferDestroy();
    OpenglWindowDestroy(openglWindow);
}

void OpenglWindowCompileShaders(OpenglWindow *openglWindow) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &openglWindow->vertexShaderSource, NULL);
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
    glShaderSource(fragmentShader, 1, &openglWindow->fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed");
    }
    // link shaders
    openglWindow->shaderProgram = glCreateProgram();
    glAttachShader(openglWindow->shaderProgram, vertexShader);
    glAttachShader(openglWindow->shaderProgram, fragmentShader);
    glLinkProgram(openglWindow->shaderProgram);
    // check for linking errors
    glGetProgramiv(openglWindow->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(openglWindow->shaderProgram, 512, NULL, infoLog);
        printf("Shader program linking failed");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OpenglWindowInit(OpenglWindow *openglWindow)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    openglWindow->glfwWindow = glfwCreateWindow(openglWindow->window->width, openglWindow->window->height,
                                                openglWindow->window->title, NULL, NULL);
    if (openglWindow->glfwWindow == NULL)
    {
        printf("Cannot create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(openglWindow->glfwWindow);

    glfwSetWindowAttrib(openglWindow->glfwWindow, GLFW_RESIZABLE, GL_FALSE);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Cannot load GLAD");
        exit(EXIT_FAILURE);
    }
}

void OpenglWindowProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void OpenglWindowLoop(OpenglWindow *openglWindow) {
    OpenglRender openglRender = OpenglRenderCreate(openglWindow);

    while (!glfwWindowShouldClose(openglWindow->glfwWindow)) {
        OpenglWindowProcessInput(openglWindow->glfwWindow);

        // Render Start
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(openglWindow->shaderProgram);

        int vertexColorLocation = glGetUniformLocation(openglWindow->shaderProgram, "vertexColor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        // Render Loop
        OpenglRenderDraw(&openglRender);

        // Render End
        glfwSwapBuffers(openglWindow->glfwWindow);
        glfwPollEvents();
    }

    OpenglRenderDestroy(&openglRender);
}

void OpenglWindowDestroy(OpenglWindow *openglWindow) {
    glDeleteProgram(openglWindow->shaderProgram);

    glfwTerminate();
}