#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Forward declaration
class playground;

class Character {
private:
    SDL_Renderer* renderer;
    SDL_Texture* sprite;
    SDL_Rect position;
    std::string name;
    bool facingRight;
    int gridX, gridY;
    
    // Colors
    SDL_Color skinColor;
    SDL_Color clothesColor;
    SDL_Color hairColor;
    
    // Hair style
    int hairStyle;  // Add this member variable
    
    // Text rendering
    TTF_Font* nameFont;
    SDL_Texture* nameTexture;
    SDL_Color nameColor;
    const playground* gamePlayground;  // Reference to playground for collision checking
    
private:
    void updateNameTexture();

public:
    // Single constructor with default values
    Character(SDL_Renderer* renderer, const std::string& name, 
             playground* pg, int startX = 0, int startY = 0);
    ~Character();
    
    // Movement methods
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void move(int dx, int dy);

    // Appearance setters
    void setSkinColor(Uint8 r, Uint8 g, Uint8 b);
    void setClothesColor(Uint8 r, Uint8 g, Uint8 b);
    void setHairColor(Uint8 r, Uint8 g, Uint8 b);
    void setHairStyle(int style);

    // Add name setter
    void setName(const std::string& newName);

    // Core methods
    void render();
    void update();
    SDL_Rect getPosition() const { return position; }
};

#endif