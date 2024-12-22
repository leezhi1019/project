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
        SDL_Texture* textTexture;  // Text texture
        std::string text;
        bool isHovered;
    };

    struct Section {
        SDL_Rect rect;      // 區域範圍
        std::string title;  // 區域標題
        bool isActive;      // 是否選中
        std::string textContent;    // For storing text content
        SDL_Texture* textTexture;   // For rendering text
    };

    struct AvatarButton {
        SDL_Rect rect;
        SDL_Texture* avatarTexture;
        bool isSelected;
        std::string avatarPath;
    };

    SDL_Texture* background;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;
    std::vector<Button> buttons;
    std::vector<Section> sections;  // 三個主要區域
    std::vector<AvatarButton> avatarButtons;
    SDL_Rect usernameInputBox;
    Button backButton;  // Declare backButton as Button
    int volumeLevel = 50;  // Default volume level

    // Private helper methods
    void createButton(const char* text, int x, int y, int width, int height);
    void handleMouseMotion(int x, int y);
    int handleMouseClick(int x, int y);
    void initializeAvatarButtons();
    void createVolumeControls(int x, int y, int width, int height);
    void updateVolumeDisplay();
    void renderDividerLines();
    void initializeUIElements(int sectionWidth, int sectionHeight);
    void initializeGameRules(int width, int height, TTF_Font* font);
    void renderSections();
    void renderUIElements();
    void initializeSettings(int width, int height, TTF_Font* font);
    void initializeScores(int width, int height, TTF_Font* font);

public:
    settings(const std::string& path, SDL_Renderer* renderer);
    ~settings();
    void render();
    int process_input(SDL_Event* event);
    void initializeSections();
};

#endif