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
    int getRange() const { return range; } // Add getter for range
    int getAngle() const { return angle; } // Add getter for angle

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
    int getVisionRange() const; // Add getter for vision range
    int getVisionAngle() const; // Add getter for vision angle
    int getAngle() const;       // Add getter for angle

    // Setters
    void setPosition(float newX, float newY);
    void setMoveSpeed(float speed) { moveSpeed = speed; }
    void setAngle(float newAngle); // Add setter for angle

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