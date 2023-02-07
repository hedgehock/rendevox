#include "../include/rendevox.h"

void drawTriangle(SDL_Renderer *renderer, vector2 v1, vector2 v2, vector2 v3, color color) {
    SDL_Vertex vertices[3];
    vertices[0] = (SDL_Vertex){(SDL_FPoint){v1.x, v1.y }, (SDL_Color){color.r, color.g, color.b, color.a }, (SDL_FPoint){0 }, };
    vertices[1] = (SDL_Vertex){(SDL_FPoint){v2.x, v2.y }, (SDL_Color){color.r, color.g, color.b, color.a }, (SDL_FPoint){0 }, };
    vertices[2] = (SDL_Vertex){(SDL_FPoint){v3.x, v3.y }, (SDL_Color){color.r, color.g, color.b, color.a }, (SDL_FPoint){0 }, };
    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
}

void drawText(SDL_Renderer *renderer, int x, int y, char *text, font font) {
    int textWidth, textHeight;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font.ttfFont, text, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    textWidth = surface->w;
    textHeight = surface->h;
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = textWidth;
    rect.h = textHeight;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
