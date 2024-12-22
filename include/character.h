#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include "constants.h" // Add this include

// Forward declaration
class playground;

class Character
{
protected:
    int gridX;
    int gridY;
    int pixelX;
    int pixelY;
    SDL_Color skinColor;
    SDL_Color clothesColor;
    SDL_Color hairColor;
    int hairStyle;
    bool facingRight;
    SDL_Texture *sprite;
    SDL_Renderer *renderer;
    SDL_Texture *currentTexture;
    std::map<std::string, SDL_Texture *> textures;

    // Name related members
    std::string name;
    TTF_Font *nameFont;
    SDL_Texture *nameTexture;
    SDL_Color nameColor;

    // Image path
    std::string imagePath;
    std::string upImage;
    std::string downImage;
    std::string leftImage;
    std::string rightImage;

private:
    // Add this private helper function
    void updateNameTexture();
    const playground *gamePlayground; // Reference to playground for collision checking

public:
    Character(SDL_Renderer *renderer, const std::string &name,
              const playground *gamePlayground, int startX = 0, int startY = 0,
              const std::string &upImage = "", const std::string &downImage = "",
              const std::string &leftImage = "", const std::string &rightImage = "");
    virtual ~Character();

    // Movement methods
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Add name setter
    void setName(const std::string &newName);
    // Position getters
    int getX() const { return gridX; }
    int getY() const { return gridY; }
    bool isFacingRight() const { return facingRight; }                                                    // Add this getter method
    SDL_Rect getPosition() const { return {gridX * GRID_SIZE, gridY * GRID_SIZE, GRID_SIZE, GRID_SIZE}; } // Add this method
    // Core methods
    virtual void render(); // Declare render as virtual
    virtual void update(); // Declare update as virtual

    const playground *getGamePlayground() const { return gamePlayground; } // Move this getter method to public

    // Add new method declarations
    void loadTextures();
    void setTexture(const std::string &direction);
    SDL_Texture *getTexture(const std::string &direction);
};

#endif