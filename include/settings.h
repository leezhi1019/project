#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "constants.h"

// Define the Button struct before the settings class
struct Button {
    SDL_Rect rect;
    const char* text;
    SDL_Texture* textTexture;
    bool isHovered;
    
    Button() : text(nullptr), textTexture(nullptr), isHovered(false) {}
};

class settings {
private:
    SDL_Renderer* renderer;
    SDL_Texture* background;
    TTF_Font* font;
    std::vector<Button> buttons;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;

public:
    settings(const std::string& path, SDL_Renderer* renderer);
    ~settings();
    
    int process_input(SDL_Event* event);
    void render();
    int update();

private:
    void createButton(const char* text, int x, int y, int width, int height);
    void handleMouseMotion(int x, int y);
    int handleMouseClick(int x, int y);
};

#endif