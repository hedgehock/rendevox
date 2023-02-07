#include <rendevox.h>

unsigned int VAO;
unsigned int VBO;

float* verticesBuffer;
unsigned int verticesBufferSize = 0;

bool debug = false;

void addVerticesToVerticesBuffer(int amount, const float* vertices) {
    if (debug == true) printf("amount: %i\n", amount);
    for (int i = 0; i < amount; i++) {
        verticesBuffer = realloc(verticesBuffer, sizeof(float) * (verticesBufferSize + 1));
        verticesBuffer[verticesBufferSize] = vertices[i];
        verticesBufferSize++;
    }
}

void cleanVerticesBuffer() {
    verticesBufferSize = 0;
    verticesBuffer = realloc(verticesBuffer, sizeof(float));
}

void renderCreateVertexArray() {
    // Bind Vertex Array
    glBindVertexArray(VAO);

    // Pass buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei)sizeof (float) * verticesBufferSize, verticesBuffer, GL_DYNAMIC_DRAW);

    // Shader attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind Vertex Array
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    if (debug == true) printf("Vertices buffer size: %i\n", verticesBufferSize);

    // Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void openglRenderCreate() {
    verticesBuffer = malloc(sizeof(float));

    // Generate Vertex array and Vertex buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

void openglRenderDestroy() {
    // Free memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void drawOpenglRender() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verticesBufferSize / 3);
    glBindVertexArray(0);
}

float lastTime = 0.0f;

void openglRenderDraw(openglWindow* openglWindow) {
    // Calculate delta time
    float currentTime = (float)glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Call user's update function and pass delta time
    userUpdate(deltaTime);

    // Main drawing loop
    for (int i = 0; i < entityBufferGetSize(); i++) {
        entity currentEntity = entityBufferGet()[i];

        if (debug == true) printf("Entity name: %s\n", currentEntity.name);

        if (strcmp(currentEntity.type, "quad") == 0) {
            float scaleX = openglWindow->windowSize.x / 1000.0f;
            float scaleY = openglWindow->windowSize.y / 1000.0f;

            float quadVertices[18];
            quadVertices[0] = currentEntity.mesh.vertices[0] * scaleY;
            quadVertices[1] = currentEntity.mesh.vertices[1] * scaleX;
            quadVertices[2] = currentEntity.mesh.vertices[2];
            quadVertices[3] = currentEntity.mesh.vertices[3] * scaleY;
            quadVertices[4] = currentEntity.mesh.vertices[4] * scaleX;
            quadVertices[5] = currentEntity.mesh.vertices[5];
            quadVertices[6] = currentEntity.mesh.vertices[6] * scaleY;
            quadVertices[7] = currentEntity.mesh.vertices[7] * scaleX;
            quadVertices[8] = currentEntity.mesh.vertices[8];
            quadVertices[9] = currentEntity.mesh.vertices[9] * scaleY;
            quadVertices[10] = currentEntity.mesh.vertices[10] * scaleX;
            quadVertices[11] = currentEntity.mesh.vertices[11];
            quadVertices[12] = currentEntity.mesh.vertices[12] * scaleY;
            quadVertices[13] = currentEntity.mesh.vertices[13] * scaleX;
            quadVertices[14] = currentEntity.mesh.vertices[14];
            quadVertices[15] = currentEntity.mesh.vertices[15] * scaleY;
            quadVertices[16] = currentEntity.mesh.vertices[16] * scaleX;
            quadVertices[17] = currentEntity.mesh.vertices[17];

            addVerticesToVerticesBuffer(18, quadVertices);
        }
    }

    // Debug purposes
    if (debug == true) {
        printf("\nNEW VERTICES BUFFER\n");
        for (int i = 0; i < verticesBufferSize; i++) {
            printf("VERTEX: %f \n", verticesBuffer[i]);
        }
    }

    renderCreateVertexArray();

    drawOpenglRender();

    cleanVerticesBuffer();
}