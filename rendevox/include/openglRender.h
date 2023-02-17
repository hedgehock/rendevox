#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

typedef struct {
    OpenglWindow* openglWindow;

    unsigned int VAO;
    unsigned int VBO;

    float* verticesBuffer;
    unsigned int verticesBufferSize;

    float lastTime;
} OpenglRender;

OpenglRender OpenglRenderCreate(OpenglWindow* openglWindow);

void OpenglRenderDraw(OpenglRender* openglRender);
void OpenglRenderAddVerticesToVerticesBuffer(OpenglRender* openglRender, int amount, const float* vertices);
void OpenglRenderCleanVerticesBuffer(OpenglRender* openglRender);
void OpenglRenderCreateVAO(OpenglRender* openglRender);

void OpenglRenderDestroy(OpenglRender* openglRender);

#endif