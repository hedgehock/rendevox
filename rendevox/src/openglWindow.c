#include <rendevox.h>

void openglWindowProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void openglWindowCreate(openglWindow *openglWindow)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    openglWindow->glfwWindow = glfwCreateWindow((int)openglWindow->windowSize.x,
                                                (int)openglWindow->windowSize.y,
                                                openglWindow->title, NULL, NULL);
    if (openglWindow->glfwWindow == NULL)
    {
        printf("Cannot create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(openglWindow->glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Cannot load GLAD");
        exit(EXIT_FAILURE);
    }

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

void openglWindowLoop(openglWindow *openglWindow, openglRender* openglRender) {
    while (!glfwWindowShouldClose(openglWindow->glfwWindow)) {
        // Handle Input
        openglWindowProcessInput(openglWindow->glfwWindow);

        // Render Start
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(openglWindow->shaderProgram);

        int vertexColorLocation = glGetUniformLocation(openglWindow->shaderProgram, "vertexColor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        // Render Loop
        openglRenderDraw(openglRender);

        // Render End
        glfwSwapBuffers(openglWindow->glfwWindow);
        glfwPollEvents();
    }
}

void openglWindowDestroy(openglWindow *openglWindow) {
    glDeleteProgram(openglWindow->shaderProgram);

    glfwTerminate();
}

void openglWindowRun(window window) {
    openglWindow openglWindow;
    openglWindow.vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                      "}\0";

    openglWindow.fragmentShaderSource = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "uniform vec4 vertexColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   FragColor = vertexColor;\n"
                                        "}\n\0";
    openglWindow.title = window.title;
    openglWindow.windowSize = (vector2){ (float)window.width, (float)window.height };
    openglWindow.debug = false;

    openglWindowCreate(&openglWindow);
    entityBufferCreate();
    openglRender openglRender = openglRenderCreate(&openglWindow);

    userStart();

    openglWindowLoop(&openglWindow, &openglRender);

    openglRenderDestroy(&openglRender);
    entityBufferDestroy();
    openglWindowDestroy(&openglWindow);
}