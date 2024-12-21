// include/bookshelf.h
#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include "obstacle.h"

class Bookshelf : public Obstacle {
private:
    const char* currentTexturePath;  // 保留材質路徑成員
    int bookCount;  // Track number of books
    void updateTexture();  // Private method to update texture
    
public:
    // 建構函式，使用預設材質
    Bookshelf(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texturePath);
    bool addBook();    // Add book to shelf
    bool removeBook(); // Remove book from shelf
    void render() override;
    int getBookCount() const { return bookCount; }

    // Constants
    static const int MAX_BOOKS = 10;
    static const int MIN_BOOKS = 0;
};

#endif