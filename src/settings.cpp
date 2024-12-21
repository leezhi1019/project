#include "../include/settings.h"
#include "../include/tool.h"  // Add this for loadTexture function
#include "../include/constants.h"

settings::settings(const std::string& path, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->background = loadTexture(path.c_str(), renderer);
    this->font = nullptr;  // Initialize to nullptr
    
    // Initialize colors
    buttonColor = {100, 100, 100, 255};
    buttonHoverColor = {150, 150, 150, 255};
    
    // Initialize font
    font = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 36);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;  // Don't create buttons if font failed to load
    }
    
    // Setup button dimensions
    int scale = 2;
    int baseWidth = 150 * scale;
    int baseHeight = 35 * scale;
    int centerX = (675 * scale - baseWidth) / 2;
    
    // Create settings buttons
    createButton("Character 1", centerX-220, 125 * scale, baseWidth, baseHeight);
    createButton("Character 2", centerX-220, 175 * scale, baseWidth, baseHeight);
    createButton("Back to Menu", centerX-220, 275 * scale, baseWidth, baseHeight);  // Added lower position

    // Initialize three sections
    int sectionWidth = WINDOW_WIDTH / 3;
    int sectionHeight = WINDOW_HEIGHT;
    
    sections.push_back({
        SDL_Rect{0, 0, sectionWidth, sectionHeight},
        "Game Rules",
        false
    });
    
    sections.push_back({
        SDL_Rect{sectionWidth, 0, sectionWidth, sectionHeight},
        "High Scores",
        false
    });
    
    sections.push_back({
        SDL_Rect{sectionWidth * 2, 0, sectionWidth, sectionHeight},
        "Settings",
        false
    });
}

settings::~settings() {
    // Clean up background texture
    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
    
    // Clean up font
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    // Clean up button textures
    for (auto& button : buttons) {
        if (button.textTexture) {
            SDL_DestroyTexture(button.textTexture);
        }
    }
}

void settings::createButton(const char* text, int x, int y, int width, int height) {
    Button button = {};  // Zero initialize the struct
    button.rect = {x, y, width, height};
    button.text = text;
    button.isHovered = false;
    
    // Create text texture
    if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, {255, 255, 255, 255});
        if (surface) {
            button.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    
    buttons.push_back(button);
}

int settings::process_input(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            handleMouseMotion(event->motion.x, event->motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                return handleMouseClick(event->button.x, event->button.y);
            }
            break;
    }
    return SETTINGSID;
}

void settings::render() {
    SDL_RenderClear(renderer);
    
    // 繪製背景
    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }
    
    // 繪製三個區域
    for (const auto& section : sections) {
        // 繪製區域邊框
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderDrawRect(renderer, &section.rect);
        
        // 繪製區域標題
        if (font) {
            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderText_Solid(font, section.title.c_str(), textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            SDL_Rect titleRect = {
                section.rect.x + 10,
                section.rect.y + 10,
                surface->w,
                surface->h
            };
            
            SDL_RenderCopy(renderer, texture, nullptr, &titleRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
    
    // 根據當前活動的區域繪製對應的按鈕
    // ...其他渲染程式碼
}

void settings::handleMouseMotion(int x, int y) {
    for (auto& button : buttons) {
        button.isHovered = (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
                           y >= button.rect.y && y <= button.rect.y + button.rect.h);
    }
}

int settings::handleMouseClick(int x, int y) {
    // 檢查點擊了哪個區域
    for (size_t i = 0; i < sections.size(); i++) {
        if (x >= sections[i].rect.x && x <= sections[i].rect.x + sections[i].rect.w &&
            y >= sections[i].rect.y && y <= sections[i].rect.y + sections[i].rect.h) {
            // 設置當前活動區域
            for (auto& section : sections) {
                section.isActive = false;
            }
            sections[i].isActive = true;
            return SETTINGSID;
        }
    }
    
    // 處理各區域內的按鈕點擊
    // ...現有的按鈕處理程式碼
}
