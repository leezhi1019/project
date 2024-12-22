#include "../include/settings.h"
#include "../include/tool.h"  // Add this for loadTexture function
#include "../include/constants.h"
#include <iostream>

void settings::initializeSections() {
    SDL_Log("Initializing sections...");
    
    sections.clear();
    
    int sectionWidth = WINDOW_WIDTH / 3;
    int sectionHeight = WINDOW_HEIGHT - 120; // Height minus bottom area
    
    // Create font only once
    TTF_Font* rulesFont = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 24);  // Smaller size for rules
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

    // Create texture for rules using the font
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(rulesFont, 
        rulesSection.textContent.c_str(), 
        textColor,
        sectionWidth - 40); // Width with margins

    if (surface) {
        rulesSection.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    TTF_CloseFont(rulesFont);
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

    // Add volume control button below avatars
    int buttonWidth = 240;
    int buttonHeight = 40;
    int spacing = 20;  // Spacing between buttons
    int buttonX = settingsSection.rect.x + (sectionWidth - buttonWidth) / 2 ;
    int buttonY = settingsSection.rect.y + 300;  // Position below avatars

    // Create volume control button
    createButton("Username", buttonX, buttonY, buttonWidth, buttonHeight);

    // Add username button below volume control
    buttonY += buttonHeight + spacing*5;  // Move down by button height plus spacing
    createButton("Volume", buttonX, buttonY, buttonWidth, buttonHeight);

    // Add volume controls below volume label
    buttonY += buttonHeight + spacing;
    createVolumeControls(buttonX, buttonY, buttonWidth, buttonHeight);

    sections.push_back(settingsSection);
}

settings::settings(const std::string& path, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->background = loadTexture(path.c_str(), renderer);
    
    // Initialize colors
    buttonColor = {100, 100, 100, 255};       // Gray
    buttonHoverColor = {150, 150, 150, 255};  // Light gray
    
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
    
    // Create back button
    createButton("Back to Menu", WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT - 80, 240, 40);
    
    // Create save button next to back button
    createButton("Save Changes", WINDOW_WIDTH/2 + 320, WINDOW_HEIGHT - 80, 240, 40);

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
                int mouseX = event->button.x;
                int mouseY = event->button.y;
                
                // Check avatar button clicks first
                for (size_t i = 0; i < avatarButtons.size(); i++) {
                    if (mouseX >= avatarButtons[i].rect.x && 
                        mouseX <= avatarButtons[i].rect.x + avatarButtons[i].rect.w &&
                        mouseY >= avatarButtons[i].rect.y && 
                        mouseY <= avatarButtons[i].rect.y + avatarButtons[i].rect.h) {
                        
                        SDL_Log("Avatar %zu clicked", i+1);
                        
                        // Deselect all avatars
                        for (auto& button : avatarButtons) {
                            button.isSelected = false;
                        }
                        // Select clicked avatar
                        avatarButtons[i].isSelected = true;
                        break;
                    }
                }
                
                // Check regular button clicks
                for (const auto& button : buttons) {
                    if (mouseX >= button.rect.x && 
                        mouseX <= button.rect.x + button.rect.w &&
                        mouseY >= button.rect.y && 
                        mouseY <= button.rect.y + button.rect.h) {
                        
                        if (button.text == "Back to Menu") {
                            return MENUID;
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

    // Draw dividing lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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

    // Render rules section
    for (const auto& section : sections) {
        // First render section title
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface* titleSurface = TTF_RenderText_Solid(font, section.title.c_str(), textColor);
        if (titleSurface) {
            SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture) {
                SDL_Rect titleRect = {
                    section.rect.x + (section.rect.w - titleSurface->w) / 2,
                    section.rect.y + 20,
                    titleSurface->w,
                    titleSurface->h
                };
                SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_FreeSurface(titleSurface);
        }

        // Then render rules content if it's the rules section
        if (section.title == "Game Rules" && section.textTexture) {
            SDL_Rect textRect = {
                section.rect.x + 20,  // Left margin
                section.rect.y + 80,  // Space below title
                section.rect.w - 40,  // Width with margins
                section.rect.h - 100
            };
            SDL_RenderCopy(renderer, section.textTexture, nullptr, &textRect);
        }
    }

    // Render avatar buttons
    for (const auto& button : avatarButtons) {
        if (button.avatarTexture) {
            SDL_RenderCopy(renderer, button.avatarTexture, nullptr, &button.rect);
        }
        
        if (button.isSelected) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black border
            for (int i = 0; i < 3; i++) {
                SDL_Rect borderRect = {
                    button.rect.x - i,
                    button.rect.y - i,
                    button.rect.w + (2 * i),
                    button.rect.h + (2 * i)
                };
                SDL_RenderDrawRect(renderer, &borderRect);
            }
        }
    }

    // Render regular buttons with hover effect
    for (const auto& button : buttons) {
        SDL_SetRenderDrawColor(renderer,
            button.isHovered ? buttonHoverColor.r : buttonColor.r,
            button.isHovered ? buttonHoverColor.g : buttonColor.g,
            button.isHovered ? buttonHoverColor.b : buttonColor.b,
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

    SDL_RenderPresent(renderer);
}

void settings::handleMouseMotion(int x, int y) {
    // Update hover states for all buttons
    for (auto& button : buttons) {
        button.isHovered = (x >= button.rect.x && 
                           x <= button.rect.x + button.rect.w &&
                           y >= button.rect.y && 
                           y <= button.rect.y + button.rect.h);
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
    int buttonSize = 100;  // Avatar button size
    int spacing = 20;      // Space between buttons
    int startX = (2 * sectionWidth) + (sectionWidth - (3 * buttonSize + 2 * spacing)) / 2;
    int startY = 150;      // Avatar buttons Y position

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

void settings::createVolumeControls(int x, int y, int width, int height) {
    // Constants for control layout
    int controlWidth = 60;  // Width of +/- buttons
    int volumeDisplayWidth = width - (2 * controlWidth);  // Width for volume number
    
    // Create minus (-) button
    createButton("-", x, y, controlWidth, height);
    
    // Create centered volume number display
    std::string volumeText = std::to_string(volumeLevel) + "%";
    createButton(volumeText.c_str(), 
                x + controlWidth, y, 
                volumeDisplayWidth, height);
    
    // Create plus (+) button
    createButton("+", 
                x + controlWidth + volumeDisplayWidth, y, 
                controlWidth, height);
}

void settings::updateVolumeDisplay() {
    // Find and update volume number button
    for (auto& button : buttons) {
        if (button.text != "+" && button.text != "-" && 
            button.text.find_first_not_of("0123456789") == std::string::npos) {
            // Update volume display
            if (button.textTexture) {
                SDL_DestroyTexture(button.textTexture);
            }
            button.text = std::to_string(volumeLevel);
            
            // Create new texture for updated number
            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderText_Solid(font, button.text.c_str(), textColor);
            if (surface) {
                button.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
            }
            break;
        }
    }
}