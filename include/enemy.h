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
    Enemy(SDL_Renderer *renderer, const std::string &name, int startX, int startY);
    ~Enemy();

    void render();
    void update();
    void setMovementPattern(void (*movementPattern)(Enemy &));

    bool detectCharacter(const Character &character) const;

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    float getMoveSpeed() const { return moveSpeed; }

    // Setters
    void setPosition(float newX, float newY);
    void setMoveSpeed(float speed) { moveSpeed = speed; }

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    std::string name;
    float x, y;
    float moveSpeed;
    int size;
    int currentWaypoint;
    int angle; // Direction the enemy is facing
    Vision vision;
    void (*movementPattern)(Enemy &); // Function pointer for movement pattern
};

#endif // ENEMY_H