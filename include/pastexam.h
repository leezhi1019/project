#pragma once
#include "collectible.h"

class PastExam : public Collectible {
private:
    int scoreMultiplier;
    float duration;

public:
    PastExam(SDL_Renderer* renderer, int x, int y);
    void collect() override;
    void update(float deltaTime) override;
};