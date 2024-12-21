#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "constants.h"

class settings {
private:
    struct Button {
        SDL_Rect rect;
        const char* text;
        bool isHovered;
        SDL_Texture* textTexture;  // Add texture for button text
    };

    struct Section {
        SDL_Rect rect;      // 區域範圍
        std::string title;  // 區域標題
        bool isActive;      // 是否選中
    };

    SDL_Texture* background;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;
    std::vector<Button> buttons;
    std::vector<Section> sections;  // 三個主要區域
    std::vector<Button> ruleButtons;     // 規則區域的按鈕
    std::vector<Button> scoreButtons;    // 分數區域的按鈕
    std::vector<Button> configButtons;   // 設定區域的按鈕

    // Private helper methods
    void createButton(const char* text, int x, int y, int width, int height);
    void handleMouseMotion(int x, int y);
    int handleMouseClick(int x, int y);

public:
    settings(const std::string& path, SDL_Renderer* renderer);
    ~settings();
    void render();
    int process_input(SDL_Event* event);
    int update();
};

#endif