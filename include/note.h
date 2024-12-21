#pragma once
#include "collectible.h"

class Note : public Collectible {
private:
    int scoreValue;

public:
    Note(SDL_Renderer* renderer, int x, int y);
    void collect() override;
};