#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "vision.h"
#include <vector>
#include <utility>

class Enemy : public Character
{
private:
    std::vector<std::pair<int, int>> patrolWaypoints;
    size_t currentWaypointIndex;
    int patrolSpeed;
    Uint32 lastMoveTime;                         // Add this to track the last move time
    static constexpr Uint32 pauseDuration = 500; // Pause duration in milliseconds
    Vision vision;                               // Add vision member
    bool characterDetected;                      // Track if character is detected
    Uint32 detectionTime;                        // Time when character was detected

public:
    Enemy(SDL_Renderer *renderer, const std::string &name, const playground *gamePlayground, int startX, int startY, const std::vector<std::pair<int, int>> &waypoints, int speed);
    void update() override;
    void render() override; // Add this method declaration
};

#endif
