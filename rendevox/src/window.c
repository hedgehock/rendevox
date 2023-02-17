#include <rendevox.h>

Window WindowCreate(const char* renderType, const char* title, int width, int height) {
    Window result;
    result.renderType = renderType;
    result.title = title;
    result.width = width;
    result.height = height;
    return result;
}

void WindowRun(Window* window) {
    if (strcmp(window->renderType, "OpenGL") == 0) {
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "uniform vec4 vertexColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vertexColor;\n"
                                           "}\n\0";

        OpenglWindow openglWindow = OpenglWindowCreate(window, vertexShaderSource, fragmentShaderSource, false);
        OpenglWindowRun(&openglWindow);
    }
    else if (strcmp(window->renderType, "Vulkan") == 0) {
        vulkanWindowRunVulkanApp(*window);
    }
}