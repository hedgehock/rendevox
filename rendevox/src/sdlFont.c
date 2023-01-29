#include "rendevox.h"

font sdlLoadFont(const char* path) {
    font tempFont;

    tempFont.ttfFont = TTF_OpenFont(path, 24);
    if (tempFont.ttfFont == NULL) {
        printf("Can't load font\n");
        exit(1);
    }

    return tempFont;
}