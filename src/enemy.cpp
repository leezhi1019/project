#include "../include/enemy.h"
#include "../include/playground.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy(SDL_Renderer *renderer, const std::string &name, const playground *gamePlayground, int startX, int startY, const std::vector<std::pair<int, int>> &waypoints, int speed,
             const std::string &upImage, const std::string &downImage,
             const std::string &leftImage, const std::string &rightImage)
    : Character(renderer, name, gamePlayground, startX, startY, upImage, downImage, leftImage, rightImage),
      patrolWaypoints(waypoints), currentWaypointIndex(0), patrolSpeed(speed), lastMoveTime(0), vision(this, 5, M_PI / 4), characterDetected(false), detectionTime(0)
{
    std::srand(std::time(nullptr)); // Seed for random direction changes
}

void Enemy::update()
{
    Uint32 currentTime = SDL_GetTicks();

    if (characterDetected)
    {
        if (currentTime - detectionTime >= 2000)
        {
            characterDetected = false; // Resume patrol after 2 seconds
        }
        else
        {
            return; // Pause for 2 seconds
        }
    }

    const playground *gamePlayground = getGamePlayground(); // Use the getter method
    if (vision.isCharacterInVision(gamePlayground->getMainCharacter()))
    {
        SDL_Log("Character detected");
        characterDetected = true;
        detectionTime = currentTime;
        return;
    }

    if (currentTime - lastMoveTime < pauseDuration)
    {
        return; // Pause for the specified duration
    }

    int nextX = gridX;
    int nextY = gridY;

    switch (currentWaypointIndex)
    {
    case 0:
        nextX += patrolSpeed;
        vision.setDirection(0); // Move right
        sprite = loadTexture(rightImage.c_str(), renderer);
        break;
    case 1:
        nextX -= patrolSpeed;
        vision.setDirection(M_PI); // Move left
        sprite = loadTexture(leftImage.c_str(), renderer);
        break;
    case 2:
        nextY += patrolSpeed;
        vision.setDirection(M_PI / 2); // Move down
        sprite = loadTexture(downImage.c_str(), renderer);
        break;
    case 3:
        nextY -= patrolSpeed;
        vision.setDirection(-M_PI / 2); // Move up
        sprite = loadTexture(upImage.c_str(), renderer);
        break;
    }

    if (nextX < 0 || nextX >= 32 || nextY < 0 || nextY >= 18 || gamePlayground->isPositionBlocked(nextX, nextY) || gamePlayground->isEnemyCollision(nextX, nextY))
    {
        // Change direction randomly
        currentWaypointIndex = std::rand() % 4;
    }
    else
    {
        gridX = nextX;
        gridY = nextY;
        lastMoveTime = currentTime; // Update the last move time
    }
}

void Enemy::render()
{
    Character::render();     // Call the base class render method
    vision.render(renderer); // Render the vision area
}
