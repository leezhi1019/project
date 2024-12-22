#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

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

    // Name related members
    std::string name;
    TTF_Font *nameFont;
    SDL_Texture *nameTexture;
    SDL_Color nameColor;

private:
    // Add this private helper function
    void updateNameTexture();
    const playground *gamePlayground; // Reference to playground for collision checking

public:
    Character(SDL_Renderer *renderer, const std::string &name,
              const playground *gamePlayground, int startX = 0, int startY = 0);
    ~Character();

    // Movement methods
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Appearance setters
    void setSkinColor(Uint8 r, Uint8 g, Uint8 b);
    void setClothesColor(Uint8 r, Uint8 g, Uint8 b);
    void setHairColor(Uint8 r, Uint8 g, Uint8 b);
    void setHairStyle(int style);

    // Add name setter
    void setName(const std::string &newName);
    // Position getters
    int getX() const { return gridX; }
    int getY() const { return gridY; }
    bool isFacingRight() const { return facingRight; } // Add this getter method
    // Core methods
    virtual void render(); // Declare render as virtual
    virtual void update(); // Declare update as virtual

    const playground *getGamePlayground() const { return gamePlayground; } // Move this getter method to public
};

#endif