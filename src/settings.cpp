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
    
    // Render background
    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }
    
    // Render buttons
    for (const auto& button : buttons) {
        SDL_SetRenderDrawColor(renderer,
            button.isHovered ? buttonHoverColor.r : buttonColor.r,
            button.isHovered ? buttonHoverColor.g : buttonColor.g,
            button.isHovered ? buttonHoverColor.b : buttonColor.b,
            255);
        SDL_RenderFillRect(renderer, &button.rect);
        
        // Change texture to textTexture to match struct member name
        if (button.textTexture) {
            int textWidth, textHeight;
            SDL_QueryTexture(button.textTexture, nullptr, nullptr, &textWidth, &textHeight);
            SDL_Rect textRect = {
                button.rect.x + (button.rect.w - textWidth) / 2,
                button.rect.y + (button.rect.h - textHeight) / 2,
                textWidth,
                textHeight
            };
            SDL_RenderCopy(renderer, button.textTexture, nullptr, &textRect);
        }
    }
    
    SDL_RenderPresent(renderer);
}

void settings::handleMouseMotion(int x, int y) {
    for (auto& button : buttons) {
        button.isHovered = (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
                           y >= button.rect.y && y <= button.rect.y + button.rect.h);
    }
}

int settings::handleMouseClick(int x, int y) {
    SDL_Log("Checking click at x:%d y:%d", x, y);
    
    for (size_t i = 0; i < buttons.size(); i++) {
        const auto& button = buttons[i];
        bool isClicked = (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
                         y >= button.rect.y && y <= button.rect.y + button.rect.h);
                         
        SDL_Log("Button %d: x:%d y:%d w:%d h:%d clicked:%d", 
                (int)i, button.rect.x, button.rect.y, button.rect.w, button.rect.h, isClicked);
                
        if (isClicked) {
            SDL_Log("Button %d clicked!", (int)i);
            switch(i) {
                case 0:  // Character 1
                    return SETTINGSID;
                case 1:  // Character 2 
                    return SETTINGSID;
                case 2:  // Back to Menu
                    return MENUID;
            }
        }
    }
    return SETTINGSID;
}
