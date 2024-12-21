#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <string>
#include "character.h"

class Vision
{
public:
    Vision(int range, int angle);
    bool isCharacterInSight(const Character &character, int enemyX, int enemyY, int enemyAngle) const;

private:
    int range;
    int angle; // Angle of the vision cone in degrees
};

class Enemy
{
public:
    Enemy(SDL_Renderer *renderer, const std::string &texturePath, int x, int y);
    ~Enemy();

    void render();
    void update();
    void setMovementPattern(void (*movementPattern)(Enemy &));

    bool detectCharacter(const Character &character) const;

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int x, y;
    int angle; // Direction the enemy is facing
    Vision vision;
    void (*movementPattern)(Enemy &); // Function pointer for movement pattern
};

#endif // ENEMY_H