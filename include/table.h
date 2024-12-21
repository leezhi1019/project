// include/table.h
#ifndef TABLE_H
#define TABLE_H

#include "obstacle.h"

class Table : public Obstacle {
private:
    const char* texturePath;  // 增加材質路徑成員
public:
    Table(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texturePath);
    void render() override;
    // Table specific functionality
    bool canPlaceItem() const;
};

#endif