#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_lib/graphics.h"
#include "include/engine.h"
#include "SDL_lib/SDL_bgi.h"
#include <SDL2/SDL_mixer.h>

int main(int argc, char *argv[]) {
    game_is_running = initialize_window();
    SDL_Window* window = SDL_CreateWindow(
        "Game Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,    // 使用新的寬度
        WINDOW_HEIGHT,   // 使用新的高度
        SDL_WINDOW_SHOWN // 移除 SDL_WINDOW_FULLSCREEN 或 SDL_WINDOW_FULLSCREEN_DESKTOP 標誌
    );
    setup();
    while (game_is_running) {
        // SDL_Log("Game is running...");
        process_input();
        game_is_running = update();
        render();
    }
    destroy_window();
    return 0;
}