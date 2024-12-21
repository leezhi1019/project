#pragma once
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "game_management.h"
#include "game_state.h"
#include <SDL2/SDL_image.h>
class ScorePage {
private:
    struct ScoreBar {
        float currentHeight;
        float targetHeight;
        SDL_Rect rect;
        SDL_Color color;
    };

    struct CollectibleDisplay {
        SDL_Texture* icon;
        int count;
        SDL_Rect position;
    };

    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<CollectibleDisplay> collectibles;
    ScoreBar scoreBar;
    SDL_Texture* menuButtonTexture;
    SDL_Rect menuButtonRect;
    bool isHovered;
    float animationTimer;
    std::string grade;
    int finalScore;

    // Add loadTexture helper function
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

    void calculateGrade();
    void updateScoreAnimation(float deltaTime);
    void renderCollectibles();
    void renderScoreBar();
    void renderGrade();

public:
    ScorePage(SDL_Renderer* renderer);
    ~ScorePage();
    void initialize();
    void update(float deltaTime);
    void render();
    int handleMouseClick(int x, int y);
    void handleMouseMotion(int x, int y);
};

// Global pointer declaration
extern ScorePage* scorePage;