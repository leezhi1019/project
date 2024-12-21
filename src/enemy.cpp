#include "../include/enemy.h"
#include "../include/tool.h"
#include <cmath>

Vision::Vision(int range, int angle) : range(range), angle(angle) {}

bool Vision::isCharacterInSight(const Character &character, int enemyX, int enemyY, int enemyAngle) const
{
    // Calculate the distance and angle to the character
    int charX = character.getX();
    int charY = charY = character.getY();
    int deltaX = charX - enemyX;
    int deltaY = charY - enemyY;
    int distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > range)
    {
        return false;
    }

    int angleToCharacter = std::atan2(deltaY, deltaX) * 180 / M_PI;
    int angleDifference = std::abs(angleToCharacter - enemyAngle);

    return angleDifference <= angle / 2;
}

Enemy::Enemy(SDL_Renderer *renderer, const std::string &texturePath, int x, int y)
    : renderer(renderer), x(x), y(y), angle(0), vision(100, 90), movementPattern(nullptr)
{
    texture = loadTexture(texturePath.c_str(), renderer);
}

Enemy::~Enemy()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Enemy::render()
{
    SDL_Rect dstRect = {x, y, 50, 50}; // Assuming the enemy is 50x50 pixels
    SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void Enemy::update()
{
    if (movementPattern)
    {
        movementPattern(*this);
    }
}

void Enemy::setMovementPattern(void (*movementPattern)(Enemy &))
{
    this->movementPattern = movementPattern;
}

bool Enemy::detectCharacter(const Character &character) const
{
    return vision.isCharacterInSight(character, x, y, angle);
}