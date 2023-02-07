typedef struct {
    openglWindow* openglWindow;

    unsigned int VAO;
    unsigned int VBO;

    float* verticesBuffer;
    unsigned int verticesBufferSize;

    // Delta time
    float lastTime;
} openglRender;

openglRender openglRenderCreate(openglWindow* openglWindow);
void openglRenderDraw(openglRender* openglRender);
void openglRenderDestroy(openglRender* openglRender);