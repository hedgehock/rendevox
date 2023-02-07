typedef struct {
    const char* renderType;
    const char* title;
    int width;
    int height;
} window;

void windowCreate(window* window);