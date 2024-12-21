#include "../include/settings.h"
#include "../include/tool.h"  // Add this for loadTexture function
#include "../include/constants.h"
#include <iostream>

void settings::initializeSections() {
    SDL_Log("Initializing sections...");
    
    // Clear existing sections
    sections.clear();
    
    int sectionWidth = WINDOW_WIDTH / 3;
    int sectionHeight = WINDOW_HEIGHT - 120; // Height minus bottom area
    
    // Create smaller font specifically for rules text
    TTF_Font* rulesFont = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 30);  // Try a different size
    if (!rulesFont) {
        SDL_Log("Failed to load rules font: %s", TTF_GetError());
        return;
    }

    // Game Rules section
    Section rulesSection;
    rulesSection.rect = {0, 0, sectionWidth, sectionHeight};
    rulesSection.title = "Game Rules";
    rulesSection.isActive = false;
    rulesSection.textContent = 
        "1.Game time limit is 1 minute.\n\n"
        " \n\n"
        "2.Collect all books and \n"
        "  old exams to get A+.\n\n"
        " \n\n"
        "3.Collision with classmates\n"
        "  deducts 5 seconds.\n\n"
        " \n\n"
        "4.Coffee power-up increases\n"
        "  collection speed.\n\n"
        " \n\n"
        "5.Phone power-up freezes\n"
        "  classmates for 3 seconds.\n\n";

    // Create texture for rules using the smaller font
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(rulesFont, 
        rulesSection.textContent.c_str(), textColor);
    if (surface) {
        rulesSection.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    TTF_CloseFont(rulesFont);  // Clean up the rules font
    sections.push_back(rulesSection);
    
    // High Scores section
    Section scoresSection;
    scoresSection.rect = {sectionWidth, 0, sectionWidth, sectionHeight};
    scoresSection.title = "High Scores";
    scoresSection.isActive = false;
    sections.push_back(scoresSection);
    
    // Settings section
    Section settingsSection;
    settingsSection.rect = {2 * sectionWidth, 0, sectionWidth, sectionHeight};
    settingsSection.title = "Settings";
    settingsSection.isActive = true;
    sections.push_back(settingsSection);
}

settings::settings(const std::string& path, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->background = loadTexture("../imgs/playground_background.jpg", renderer);
    
    // Initialize font
    font = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 36);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    // Initialize sections
    initializeSections();
    
    // Initialize avatar buttons
    initializeAvatarButtons();
    
    // Create back button last so it appears on top
    createButton("Back to Menu", WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT - 80, 240, 40);

    SDL_StartTextInput();
}

settings::~settings() {
    // Clean up button textures
    for (auto& button : buttons) {
        if (button.textTexture) {
            SDL_DestroyTexture(button.textTexture);
            button.textTexture = nullptr;
        }
    }
    
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
}

void settings::createButton(const char* text, int x, int y, int width, int height) {
    Button button;
    button.rect = {x, y, width, height};
    button.text = text;
    button.isHovered = false;
    button.textTexture = nullptr;  // Initialize to nullptr

    // Create text texture with error checking
    if (font) {
        SDL_Color textColor = {255, 255, 255, 255};  // White text
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
        
        if (surface) {
            button.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            
            if (!button.textTexture) {
                SDL_Log("Failed to create texture: %s", SDL_GetError());
            }
        } else {
            SDL_Log("Failed to create text surface: %s", TTF_GetError());
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
            
        case SDL_TEXTINPUT:
            // Add text input to active section
            for (auto& section : sections) {
                if (section.isActive && section.title == "Game Rules") {
                    // Add the typed text
                    section.textContent += event->text.text;
                    SDL_Log("Text content updated: %s", section.textContent.c_str());
                    
                    // Clean up old texture
                    if (section.textTexture) {
                        SDL_DestroyTexture(section.textTexture);
                        section.textTexture = nullptr;
                    }
                    
                    // Create new texture with error checking
                    SDL_Color textColor = {0, 0, 0, 255};  // Black text
                    SDL_Surface* surface = TTF_RenderText_Solid(font, 
                        section.textContent.c_str(), textColor);
                        
                    if (!surface) {
                        SDL_Log("Failed to create text surface: %s", TTF_GetError());
                        continue;
                    }
                    
                    section.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (!section.textTexture) {
                        SDL_Log("Failed to create texture: %s", SDL_GetError());
                    }
                    SDL_FreeSurface(surface);
                }
            }
            break;
            
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_BACKSPACE) {
                // Handle backspace
                for (auto& section : sections) {
                    if (section.isActive && section.title == "Game Rules") {
                        if (!section.textContent.empty()) {
                            section.textContent.pop_back();
                            // Recreate texture
                            if (section.textTexture) {
                                SDL_DestroyTexture(section.textTexture);
                            }
                            SDL_Color textColor = {0, 0, 0, 255};
                            SDL_Surface* surface = TTF_RenderText_Solid(font, 
                                section.textContent.c_str(), textColor);
                            if (surface) {
                                section.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
                                SDL_FreeSurface(surface);
                            }
                        }
                    }
                }
            }
            break;
    }
    return SETTINGSID;
}

void settings::render() {
    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }

    // Draw vertical dividing lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black lines

    // Draw thick vertical lines
    for(int i = 0; i < 3; i++) {
        SDL_RenderDrawLine(renderer, 
            (WINDOW_WIDTH / 3) + i - 1, 0,
            (WINDOW_WIDTH / 3) + i - 1, WINDOW_HEIGHT);
        
        SDL_RenderDrawLine(renderer, 
            (2 * WINDOW_WIDTH / 3) + i - 1, 0,
            (2 * WINDOW_WIDTH / 3) + i - 1, WINDOW_HEIGHT);
    }
    
    // Draw thick horizontal line
    for(int i = 0; i < 3; i++) {
        SDL_RenderDrawLine(renderer,
            0, WINDOW_HEIGHT - 120 + i - 1,
            WINDOW_WIDTH, WINDOW_HEIGHT - 120 + i - 1);
    }

    // Render section titles only once with black text
    if (font) {
        SDL_Color textColor = {0, 0, 0, 255};  // Black text only
        
        for (const auto& section : sections) {
            SDL_Surface* surface = TTF_RenderText_Solid(font, section.title.c_str(), textColor);
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    SDL_Rect titleRect = {
                        section.rect.x + (section.rect.w - surface->w) / 2,
                        section.rect.y + 20,
                        surface->w,
                        surface->h
                    };
                    SDL_RenderCopy(renderer, texture, nullptr, &titleRect);
                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }
    }

    // Render avatar buttons
    for (const auto& button : avatarButtons) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderDrawRect(renderer, &button.rect);
        
        if (button.avatarTexture) {
            SDL_RenderCopy(renderer, button.avatarTexture, nullptr, &button.rect);
        }
        
        if (button.isSelected) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_Rect highlightRect = button.rect;
            highlightRect.x -= 2;
            highlightRect.y -= 2;
            highlightRect.w += 4;
            highlightRect.h += 4;
            SDL_RenderDrawRect(renderer, &highlightRect);
        }
    }

    // Render back button last
    for (const auto& button : buttons) {
        SDL_SetRenderDrawColor(renderer, 
            button.isHovered ? 150 : 100,
            button.isHovered ? 150 : 100,
            button.isHovered ? 150 : 100,
            255);
        SDL_RenderFillRect(renderer, &button.rect);

        if (button.textTexture) {
            SDL_Rect textRect = button.rect;
            SDL_QueryTexture(button.textTexture, NULL, NULL, &textRect.w, &textRect.h);
            textRect.x = button.rect.x + (button.rect.w - textRect.w) / 2;
            textRect.y = button.rect.y + (button.rect.h - textRect.h) / 2;
            SDL_RenderCopy(renderer, button.textTexture, NULL, &textRect);
        }
    }

    // Render rules text with line breaks
    for (const auto& section : sections) {
        if (section.title == "Game Rules" && !section.textContent.empty()) {
            // Create smaller font for rules
            TTF_Font* rulesFont = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 30);
            if (!rulesFont) {
                SDL_Log("Failed to load rules font: %s", TTF_GetError());
                continue;
            }

            SDL_Color textColor = {0, 0, 0, 255};  // Black text
            int yOffset = 80;  // Starting Y position below title
            
            // Split the text by newlines and render each line
            std::string text = section.textContent;
            size_t pos = 0;
            std::string line;
            
            while ((pos = text.find("\n")) != std::string::npos) {
                line = text.substr(0, pos);
                if (!line.empty()) {
                    SDL_Surface* surface = TTF_RenderText_Solid(rulesFont, line.c_str(), textColor);
                    if (surface) {
                        SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(renderer, surface);
                        if (lineTexture) {
                            SDL_Rect textRect = {
                                section.rect.x + 20,  // Left margin
                                section.rect.y + yOffset,
                                surface->w,
                                surface->h
                            };
                            SDL_RenderCopy(renderer, lineTexture, nullptr, &textRect);
                            SDL_DestroyTexture(lineTexture);
                            yOffset += surface->h + 5;  // Add spacing between lines
                        }
                        SDL_FreeSurface(surface);
                    }
                }
                text.erase(0, pos + 1);
            }
            
            // Render the last line if any
            if (!text.empty()) {
                SDL_Surface* surface = TTF_RenderText_Solid(rulesFont, text.c_str(), textColor);
                if (surface) {
                    SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (lineTexture) {
                        SDL_Rect textRect = {
                            section.rect.x + 20,
                            section.rect.y + yOffset,
                            surface->w,
                            surface->h
                        };
                        SDL_RenderCopy(renderer, lineTexture, nullptr, &textRect);
                        SDL_DestroyTexture(lineTexture);
                    }
                    SDL_FreeSurface(surface);
                }
            }
            
            TTF_CloseFont(rulesFont);
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
    // Check back button click first
    for (size_t i = 0; i < buttons.size(); i++) {
        if (x >= buttons[i].rect.x && x <= buttons[i].rect.x + buttons[i].rect.w &&
            y >= buttons[i].rect.y && y <= buttons[i].rect.y + buttons[i].rect.h) {
            SDL_Log("Back button clicked, returning MENUID (0)");
            return MENUID;  // Return 0 for menu
        }
    }

    // Check section clicks
    for (size_t i = 0; i < sections.size(); i++) {
        if (x >= sections[i].rect.x && x <= sections[i].rect.x + sections[i].rect.w &&
            y >= sections[i].rect.y && y <= sections[i].rect.y + sections[i].rect.h) {
            for (auto& section : sections) {
                section.isActive = false;
            }
            sections[i].isActive = true;
            return SETTINGSID;
        }
    }

    // Check avatar button clicks
    for (size_t i = 0; i < avatarButtons.size(); i++) {
        if (x >= avatarButtons[i].rect.x && x <= avatarButtons[i].rect.x + avatarButtons[i].rect.w &&
            y >= avatarButtons[i].rect.y && y <= avatarButtons[i].rect.y + avatarButtons[i].rect.h) {
            for (auto& button : avatarButtons) {
                button.isSelected = false;
            }
            avatarButtons[i].isSelected = true;
            return SETTINGSID;
        }
    }

    return SETTINGSID;
}

void settings::initializeAvatarButtons() {
    int sectionWidth = WINDOW_WIDTH / 3;
    int buttonSize = 100;
    int spacing = 20;
    int startX = 2 * sectionWidth + (sectionWidth - 3 * buttonSize - 2 * spacing) / 2;
    int startY = 100;

    // Clear existing buttons if any
    avatarButtons.clear();

    // Add debug logging
    SDL_Log("Initializing avatar buttons...");

    for (int i = 0; i < 3; i++) {
        AvatarButton button;
        button.rect = {
            startX + i * (buttonSize + spacing),
            startY,
            buttonSize,
            buttonSize
        };
        
        std::string imagePath = "../imgs/avatar" + std::to_string(i+1) + ".png";
        SDL_Log("Loading avatar image: %s", imagePath.c_str());
        
        button.avatarTexture = loadTexture(imagePath.c_str(), renderer);
        if (!button.avatarTexture) {
            SDL_Log("Failed to load avatar %d texture", i+1);
        }
        
        button.isSelected = (i == 0);
        avatarButtons.push_back(button);
    }
}
