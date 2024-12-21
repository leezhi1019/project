#ifndef CONSTANTS_H
#define CONSTANTS_H

// Boolean constants
const int TRUE = 1;
const int FALSE = 0;
const int EXIT = -1;

// Window dimensions, frame rates, etc.
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1200
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define PLAYER_W 20
#define PLAYER_H 100
#define PLAYER_SPEED 3000
#define MENU_BACKGROUND "../imgs/background.jpg"
#define PLAYGROUND_BACKGROUND "../imgs/playground_background.jpg"
#define SETTINGS_BACKGROUND "../imgs/settings_background.jpg"
#define BOOKSHELF_TEXTURE "../imgs/bookshelf_image.jpg"
#define TABLE_TEXTURE "../imgs/table-bag-2x2.png"

// Grid size for game world
#define GRID_SIZE 40  // Size of each grid cell in pixels

#endif // STUDYSNATCHER_CONSTANTS_H
