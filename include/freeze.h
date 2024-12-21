#pragma once
#include "collectible.h"

class Freeze : public Collectible {
private:
    float freezeDuration;
    bool isActive;
    float powerupTimer;

protected:
    void renderGlow() override;

public:
    Freeze(SDL_Renderer* renderer, int x, int y);
    void collect() override;
    void update(float deltaTime) override;
    bool isFreezingActive() const { return isActive; }
};