#ifndef CONSTANTS_H
#define CONSTANTS_H

// Game states/IDs
#define MENUID 0       // Menu page ID
#define SETTINGSID 1   // Settings page ID
#define PLAYGROUNDID 2 // Playground page ID
#define EXIT 3         // Exit game ID

// Boolean constants
const int TRUE = 1;
const int FALSE = 0;

// Add any other constants here
// Window dimensions, frame rates, etc.
// 修改視窗大小常數
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1320
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define PLAYER_W 20
#define PLAYER_H 100
#define PLAYER_SPEED 3000
#define MENU_BACKGROUND "../imgs/background.jpg"
#define PLAYGROUND_BACKGROUND "../imgs/playground_background.jpg"
#define SETTINGS_BACKGROUND "../imgs/playground_background.jpg"

#define BOOKSHELF_TEXTURE_2x1 "../imgs/bookshelf-2x1.png"
#define BOOKSHELF_TEXTURE_3x1 "../imgs/bookshelf-3x1.png"
#define BOOKSHELF_TEXTURE_4x1 "../imgs/bookshelf-4x1.png"
#define BOOKSHELF_TEXTURE_4x2 "../imgs/bookshelf-4x2.png"
#define BOOKSHELF_TEXTURE_UP "../imgs/bookshelf-up-4x14.png"
#define BOOKSHELF_TEXTURE_LEFT "../imgs/bookshelf-left-1x14.png"
#define BOOKSHELF_TEXTURE_RIGHT "../imgs/bookshelf-right-1x14.png"
#define DEFAULT_BOOKSHELF_TEXTURE BOOKSHELF_TEXTURE_LEFT  // Add this line


#define TABLE_TEXTURE_1x1bag "../imgs/table-bag-1x1.png"
#define TABLE_TEXTURE_2x2bag "../imgs/table-bag-2x2.png"
#define TABLE_TEXTURE_1x1book "../imgs/table-book-1x1.png"
#define TABLE_TEXTURE_2x2book "../imgs/table-book-2x2.png"
#define DEFAULT_TABLE_TEXTURE TABLE_TEXTURE_1x1book  // Add this line

// Grid size for game world
#define GRID_SIZE 40  // Size of each grid cell in pixels

// Define line properties
#define LINE_COLOR_R 0     // Red component
#define LINE_COLOR_G 0     // Green component
#define LINE_COLOR_B 0     // Black component
#define LINE_COLOR_A 255   // Alpha (opacity)
#define LINE_WIDTH 2       // Width of the line in pixels

#endif // STUDYSNATCHER_CONSTANTS_H
