#include "../include/score_page.h"
#include "../include/game_management.h"
#include "../include/game_state.h"
#include "../include/audio_manager.h" // Add this include if not present

ScorePage::ScorePage(SDL_Renderer *renderer) : renderer(renderer), animationTimer(0)
{
    font = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 36);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    // Load textures with error checking
    SDL_Texture *noteIcon = loadTexture("../imgs/note.png", renderer);
    SDL_Texture *examIcon = loadTexture("../imgs/pastexam.png", renderer);
    SDL_Texture *coffeeIcon = loadTexture("../imgs/coffee.png", renderer);
    SDL_Texture *freezeIcon = loadTexture("../imgs/freeze.png", renderer);

    if (!noteIcon || !examIcon || !coffeeIcon || !freezeIcon)
    {
        SDL_Log("Failed to load one or more collectible textures");
    }

    // Position icons and counts in a grid
    int startX = 200;
    int startY = 100;
    int spacing = 150;

    collectibles = {
        {noteIcon, GameManagement::getNoteCount(), {startX, startY, 64, 64}},
        {examIcon, GameManagement::getExamCount(), {startX + spacing, startY, 64, 64}},
        {coffeeIcon, GameManagement::getCoffeeCount(), {startX, startY + spacing, 64, 64}},
        {freezeIcon, GameManagement::getFreezeCount(), {startX + spacing, startY + spacing, 64, 64}}};

    // Initialize score bar
    scoreBar = {
        0,                   // currentHeight
        0,                   // targetHeight will be set in initialize()
        {500, 100, 40, 400}, // position and size
        {50, 200, 50, 255}   // color
    };

    // Create menu button
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Back to Menu", textColor);
    menuButtonTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    menuButtonRect = {550, 600, 200, 50};
    isHovered = false;
}

ScorePage::~ScorePage()
{
    if (font)
        TTF_CloseFont(font);
    if (menuButtonTexture)
        SDL_DestroyTexture(menuButtonTexture);
    for (auto &item : collectibles)
    {
        if (item.icon)
            SDL_DestroyTexture(item.icon);
    }
}

void ScorePage::initialize()
{
    // Calculate final score based on collectibles
    finalScore = GameManagement::calculateFinalScore();
    scoreBar.targetHeight = (float)(finalScore * scoreBar.rect.h) / 100.0f;
    calculateGrade();

    // Load and play the corresponding sound effect based on grade
    if (grade == "A+")
    {
        AudioManager::loadMusic("../audio/score_aplus.mp3");
    }
    else if (grade == "A")
    {
        AudioManager::loadMusic("../audio/score_a.mp3");
    }
    else if (grade == "A-")
    {
        AudioManager::loadMusic("../audio/score_aminus.mp3");
    }
    else if (grade == "B+")
    {
        AudioManager::loadMusic("../audio/score_bplus.mp3");
    }
    else if (grade == "B")
    {
        AudioManager::loadMusic("../audio/score_b.mp3");
    }
    else if (grade == "B-")
    {
        AudioManager::loadMusic("../audio/score_bminus.mp3");
    }
    else if (grade == "C+")
    {
        AudioManager::loadMusic("../audio/score_cplus.mp3");
    }
    else if (grade == "C")
    {
        AudioManager::loadMusic("../audio/score_c.mp3");
    }
    else if (grade == "F")
    {
        AudioManager::loadMusic("../audio/score_f.mp3");
    }
    AudioManager::playMusic();

    animationTimer = 0;
    scoreBar.currentHeight = 0;

    // Update collectible counts
    collectibles[0].count = GameManagement::getNoteCount();
    collectibles[1].count = GameManagement::getExamCount();
    collectibles[2].count = GameManagement::getCoffeeCount();
    collectibles[3].count = GameManagement::getFreezeCount();
}

void ScorePage::updateScoreAnimation(float deltaTime)
{
    const float ANIMATION_SPEED = 200.0f;
    if (scoreBar.currentHeight < scoreBar.targetHeight)
    {
        scoreBar.currentHeight += ANIMATION_SPEED * deltaTime;
        if (scoreBar.currentHeight > scoreBar.targetHeight)
        {
            scoreBar.currentHeight = scoreBar.targetHeight;
        }
    }
}

void ScorePage::calculateGrade()
{
    if (finalScore >= 100)
        grade = "A+";
    else if (finalScore >= 90)
        grade = "A";
    else if (finalScore >= 85)
        grade = "A-";
    else if (finalScore >= 80)
        grade = "B+";
    else if (finalScore >= 75)
        grade = "B";
    else if (finalScore >= 70)
        grade = "B-";
    else if (finalScore >= 65)
        grade = "C+";
    else if (finalScore >= 60)
        grade = "C";
    else
        grade = "F"; // Changed from C to F for scores below 60
}

void ScorePage::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render character if available
    if (characterTexture)
    {
        SDL_RenderCopy(renderer, characterTexture, nullptr, &characterRect);
    }

    renderCollectibles();
    renderScoreBar();
    renderGrade();

    // Render menu button
    SDL_SetRenderDrawColor(renderer, isHovered ? 150 : 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &menuButtonRect);
    SDL_RenderCopy(renderer, menuButtonTexture, NULL, &menuButtonRect);

    SDL_RenderPresent(renderer);
}

void ScorePage::renderCollectibles()
{
    for (const auto &item : collectibles)
    {
        SDL_RenderCopy(renderer, item.icon, NULL, &item.position);

        // Render count next to icon
        SDL_Color textColor = {255, 255, 255, 255};
        std::string countText = std::to_string(item.count);
        SDL_Surface *surface = TTF_RenderText_Solid(font, countText.c_str(), textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect countRect = {
            item.position.x + item.position.w + 10,
            item.position.y + (item.position.h - surface->h) / 2,
            surface->w,
            surface->h};

        SDL_RenderCopy(renderer, texture, NULL, &countRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void ScorePage::renderScoreBar()
{
    // Render bar background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &scoreBar.rect);

    // Render current score level
    SDL_Rect fillRect = scoreBar.rect;
    fillRect.h = (int)scoreBar.currentHeight;
    fillRect.y = scoreBar.rect.y + (scoreBar.rect.h - fillRect.h);
    SDL_SetRenderDrawColor(renderer,
                           scoreBar.color.r,
                           scoreBar.color.g,
                           scoreBar.color.b,
                           scoreBar.color.a);
    SDL_RenderFillRect(renderer, &fillRect);
}

void ScorePage::renderGrade()
{
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, grade.c_str(), textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect gradeRect = {
        scoreBar.rect.x + scoreBar.rect.w + 20,
        scoreBar.rect.y + (scoreBar.rect.h - surface->h) / 2,
        surface->w,
        surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &gradeRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int ScorePage::handleMouseClick(int x, int y)
{
    if (x >= menuButtonRect.x && x <= menuButtonRect.x + menuButtonRect.w &&
        y >= menuButtonRect.y && y <= menuButtonRect.y + menuButtonRect.h)
    {
        return MENUID;
    }
    return SCOREID;
}

void ScorePage::handleMouseMotion(int x, int y)
{
    isHovered = (x >= menuButtonRect.x && x <= menuButtonRect.x + menuButtonRect.w &&
                 y >= menuButtonRect.y && y <= menuButtonRect.y + menuButtonRect.h);
}
void ScorePage::update(float deltaTime) { updateScoreAnimation(deltaTime); }
SDL_Texture *ScorePage::loadTexture(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load image %s: %s", path.c_str(), IMG_GetError());
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Failed to create texture from %s: %s", path.c_str(), SDL_GetError());
        SDL_FreeSurface(surface);
        return nullptr;
    }

    SDL_FreeSurface(surface);
    return texture;
}

std::string ScorePage::getScore()
{
    return score; // Return the score
}