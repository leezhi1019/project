#include "../include/enemy.h"
#include "../include/tool.h"
#include <cmath>

Vision::Vision(int range, int angle) : range(range), angle(angle) {}

bool Vision::isCharacterInSight(const Character &character, int enemyX, int enemyY, int enemyAngle) const
{
    // Calculate the distance and angle to the character
    int charX = character.getX();
    int charY = character.getY();
    int deltaX = charX - enemyX;
    int deltaY = charY - enemyY;
    int distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > range)
    {
        return false;
    }

    float angleToCharacter = std::atan2(deltaY, deltaX) * 180 / M_PI;
    float angleDifference = std::fmod(std::abs(angleToCharacter - enemyAngle), 360.0f);

    if (angleDifference > 180.0f)
    {
        angleDifference = 360.0f - angleDifference;
    }

    return angleDifference <= angle / 2;
}

Enemy::Enemy(SDL_Renderer *renderer, const std::string &name, int startX, int startY)
    : renderer(renderer),
      name(name),
      x(startX),
      y(startY),
      moveSpeed(2.0f),
      size(32), // Set size to be the same as the main character's size
      currentWaypoint(0),
      angle(0),
      vision(250, 60), // Initialize vision with 250 range and 60 degree angle
      movementPattern(nullptr)
{
    // Create red square texture
    SDL_Surface *surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
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
    SDL_Rect destRect = {static_cast<int>(x), static_cast<int>(y), size, size};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
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

void Enemy::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

void Enemy::setAngle(float newAngle)
{
    angle = newAngle;
}

int Enemy::getVisionRange() const
{
    return vision.getRange();
}

int Enemy::getVisionAngle() const
{
    return vision.getAngle();
}

int Enemy::getAngle() const
{
    return angle;
}