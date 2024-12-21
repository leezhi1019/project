// include/bookshelf.h
#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include "obstacle.h"

class Bookshelf : public Obstacle {
private:
    const char* currentTexturePath;  // 保留材質路徑成員
    
public:
    // 建構函式，使用預設材質
    Bookshelf(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texturePath);
    void render() override;
};

#endif