#include "../include/vision.h"
#include "../include/constants.h" // Include this for GRID_SIZE
#include <cmath>

Vision::Vision(const Character *owner, int range, float angle)
    : owner(owner), range(range), angle(angle), direction(0) {}

bool Vision::isCharacterInVision(const Character *character) const
{
    int ownerX = owner->getX();
    int ownerY = owner->getY();
    int charX = character->getX();
    int charY = character->getY();

    int dx = charX - ownerX;
    int dy = charY - ownerY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > range)
    {
        return false;
    }

    float angleToCharacter = std::atan2(dy, dx);

    // Normalize the angle difference to the range [-PI, PI]
    float diff = std::fmod(direction - angleToCharacter + M_PI, 2 * M_PI) - M_PI;
    return std::fabs(diff) <= angle / 2;
}

void Vision::render(SDL_Renderer *renderer) const
{
    int ownerX = owner->getX() * GRID_SIZE + GRID_SIZE / 2;
    int ownerY = owner->getY() * GRID_SIZE + GRID_SIZE / 2;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // Semi-transparent red

    for (float a = -angle / 2; a <= angle / 2; a += 0.01)
    {
        float endX = ownerX + range * GRID_SIZE * std::cos(direction + a);
        float endY = ownerY + range * GRID_SIZE * std::sin(direction + a);
        SDL_RenderDrawLine(renderer, ownerX, ownerY, endX, endY);
    }
}

void Vision::setDirection(float newDirection)
{
    direction = newDirection;
}
