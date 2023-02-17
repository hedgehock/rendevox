#ifndef WINDOW_H
#define WINDOW_H

typedef struct {
    const char* renderType;
    const char* title;
    int width;
    int height;
} Window;

Window WindowCreate(const char* renderType, const char* title, int width, int height);
void WindowRun(Window* window);

#endif