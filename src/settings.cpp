#include "../include/settings.h"
#include "../include/tool.h"  // Add this for loadTexture function
#include "../include/constants.h"
#include "../include/game_state.h"
settings::settings(const std::string& path, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->background = loadTexture(path.c_str(), renderer);
    this->font = nullptr;  // Initialize to nullptr
    
    // Initialize colors
    buttonColor = {100, 100, 100, 255};
    buttonHoverColor = {150, 150, 150, 255};
    
    // Initialize font with larger size for title
    font = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 48);  // Bigger font for title
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }
    
    // Create title text texture
    SDL_Color titleColor = {255, 255, 255, 255};  // White color
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Choose your subject", titleColor);
    if (titleSurface) {
        titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        titleRect = {0, 0, titleSurface->w, titleSurface->h};
        SDL_FreeSurface(titleSurface);
    }
    
    // Setup button dimensions
    int scale = 2;
    int baseWidth = 150 * scale;
    int baseHeight = 35 * scale;
    int centerX = (675 * scale - baseWidth) / 2;
    
    // Create only the Back to Menu button
    createButton("Back to Menu", centerX, 325 * scale, baseWidth + 50, baseHeight);
//new add
    // Initialize character options
    const char* characterPaths[] = {
        "../imgs/book1.png",
        "../imgs/book2.png", 
        "../imgs/book3.png"
    };
//new add ends here

    // Calculate positions for character options
    int screenWidth = 1350;
    int screenHeight = 772;
    int quarterWidth = screenWidth / 2;
    int startX = screenWidth / 2;
    int startY = 150;  // Increased from 20 to 150 to move options lower
    
    // Center the title above the character options
    titleRect.x = startX + (quarterWidth - titleRect.w) / 2;
    titleRect.y = startY - 80;  // Position title above the character options
    
    int optionWidth = 200;
    int optionHeight = 250;
    int spacing = 25;
    
    int totalWidth = (3 * optionWidth) + (2 * spacing);
    startX = screenWidth/2 + (quarterWidth - totalWidth)/2;
    
    // Create character options
    for (int i = 0; i < 3; i++) {
        CharacterOption option;
        option.texture = loadTexture(characterPaths[i], renderer);
        option.rect = {
            startX + (i * (optionWidth + spacing)),
            startY,
            optionWidth,
            optionHeight
        };
        option.isSelected = (i == selectedCharacter);
        characterOptions.push_back(option);
    }
    //new add
    initializeRules();  // 新增: 初始化規則文字
    //new add ends here
}

settings::~settings() {
    if (titleTexture) {
        SDL_DestroyTexture(titleTexture);
        titleTexture = nullptr;
    }
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
    
    // Render title
    if (titleTexture) {
        SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    }
    
    // Render character options
    for (const auto& option : characterOptions) {
        // Render character image
        SDL_RenderCopy(renderer, option.texture, nullptr, &option.rect);
        
        // If selected, render white bezel
        if (option.isSelected) {
            //new add
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            //new add ends here
            SDL_Rect bezel = option.rect;
            // Draw thicker border
            for (int i = 0; i < 4; i++) {
                SDL_RenderDrawRect(renderer, &bezel);
                bezel.x++;
                bezel.y++;
                bezel.w -= 2;
                bezel.h -= 2;
            }
        }
    }
    
    // Render back button
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
    //new add
    // 新增: 渲染規則文字
    if (rulesTexture) {
        SDL_Rect destRect = {20, 80, WINDOW_WIDTH/3 - 40, WINDOW_HEIGHT - 200};
        SDL_RenderCopy(renderer, rulesTexture, nullptr, &destRect);
    }
//new add ends here
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
    
    // Check character options first
    for (size_t i = 0; i < characterOptions.size(); i++) {
        const auto& option = characterOptions[i];
        if (x >= option.rect.x && x <= option.rect.x + option.rect.w &&
            y >= option.rect.y && y <= option.rect.y + option.rect.h) {
            // Deselect all options
            for (auto& opt : characterOptions) {
                opt.isSelected = false;
            }
            // Select clicked option
            characterOptions[i].isSelected = true;
            selectedCharacter = i;
            return SETTINGSID;
        }
    }
    
    // Check back button
    for (size_t i = 0; i < buttons.size(); i++) {
        const auto& button = buttons[i];
        bool isClicked = (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
                         y >= button.rect.y && y <= button.rect.y + button.rect.h);
        
        SDL_Log("Button %d: x:%d y:%d w:%d h:%d clicked:%d", 
                (int)i, button.rect.x, button.rect.y, button.rect.w, button.rect.h, isClicked);
                
        if (isClicked) {
            return MENUID;  // Since we only have one "Back to Menu" button
        }
    }
    return SETTINGSID;
}

int settings::update() {
    // Basic update implementation
    return SETTINGSID;  // Return current page ID
}
// new add
void settings::initializeRules() {
    // 新增: 規則文字內容
    std::string rulesText = 
        "1.Game time limit is 1 minute.\n\n"
        " \n\n"
        "2.Collect all books and \n"
        "  old exams to get A+.\n\n"
        " \n\n"
        "3.Discovered by classmates\n"
        "  deducts 5 seconds.\n\n"
        " \n\n"
        "4.Coffee power-up doubles\n"
        "  collection speed.\n\n"
        " \n\n"
        "5.Phone power-up freezes\n"
        "  classmates for 3 seconds.\n\n"
        " \n\n"
        "6.Press E to collect items.\n\n";

    // 新增: 確保字體載入成功
    TTF_Font* rulesFont = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 24);
    if (!rulesFont) {
        SDL_Log("Failed to load rules font: %s", TTF_GetError());
        return;
    }

    // 新增: 創建文字表面
    SDL_Color textColor = {0, 0, 0, 255};  // 黑色文字
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(rulesFont, 
        rulesText.c_str(), 
        textColor, 
        WINDOW_WIDTH/3 - 40);  // 設定文字換行寬度為視窗寬度的1/3減去邊距

    // 新增: 檢查並創建材質
    if (surface) {
        if (rulesTexture) {
            SDL_DestroyTexture(rulesTexture);  // 如果已存在則先銷毀
        }
        rulesTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    TTF_CloseFont(rulesFont);  // 記得關閉字體
}
