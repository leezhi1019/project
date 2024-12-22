#include "../include/character.h"
#include "../include/tool.h"
#include "../include/playground.h" // Add this include

Character::Character(SDL_Renderer *renderer, const std::string &name,
                     const playground *playground, int startX, int startY,
                     const std::string &upImage, const std::string &downImage,
                     const std::string &leftImage, const std::string &rightImage)
    : renderer(renderer), name(name), gamePlayground(playground),
      gridX(startX), gridY(startY), facingRight(true),
      sprite(nullptr), nameFont(nullptr), nameTexture(nullptr), // Initialize all pointers
      skinColor{255, 200, 150, 255},                            // Default skin color
      clothesColor{255, 255, 255, 255},                         // Default clothes color
      hairColor{100, 50, 0, 255},                               // Default hair color
      nameColor{255, 255, 255, 255},                            // Default name color
      upImage(upImage), downImage(downImage), leftImage(leftImage), rightImage(rightImage)
{
    SDL_Log("Initializing character...");

    // Log the base path for debugging
    SDL_Log("Base path: %s", SDL_GetBasePath());

    // Load initial sprite
    if (!downImage.empty())
    {
        SDL_Log("Loading character sprite from: %s", downImage.c_str());
        sprite = loadTexture(downImage.c_str(), renderer);
        if (!sprite)
        {
            SDL_Log("Failed to load character sprite from %s: %s", downImage.c_str(), SDL_GetError());
        }
    }

    // Ensure the sprite is loaded immediately after initialization
    if (!sprite)
    {
        SDL_Log("Sprite is null after initialization, attempting to reload.");
        sprite = loadTexture(downImage.c_str(), renderer);
        if (!sprite)
        {
            SDL_Log("Failed to reload character sprite from %s: %s", downImage.c_str(), SDL_GetError());
        }
    }

    // Initialize font for name tag
    nameFont = TTF_OpenFont("../fonts/Action_Man_Bold.ttf", 16);
    if (!nameFont)
    {
        SDL_Log("Failed to load name font: %s", TTF_GetError());
        return; // Early return on failure
    }
    SDL_Log("Name font loaded.");

    // Create name texture
    updateNameTexture();
    if (!nameTexture)
    {
        SDL_Log("Failed to create name texture!");
        return;
    }
    SDL_Log("Name texture created.");

    SDL_Log("Character initialized successfully.");
}

Character::~Character()
{
    if (sprite)
    {
        SDL_DestroyTexture(sprite);
    }
    if (nameTexture)
    {
        SDL_DestroyTexture(nameTexture);
    }
    if (nameFont)
    {
        TTF_CloseFont(nameFont);
    }
}

void Character::moveLeft()
{
    if (gridX > 0 && !gamePlayground->isPositionBlocked(gridX - 1, gridY))
    {
        gridX--;
        facingRight = false;
        if (!leftImage.empty())
        {
            SDL_Log("Loading character sprite from: %s", leftImage.c_str());
            SDL_Texture *newSprite = loadTexture(leftImage.c_str(), renderer);
            if (newSprite)
            {
                SDL_DestroyTexture(sprite);
                sprite = newSprite;
            }
            else
            {
                SDL_Log("Failed to load character sprite from %s: %s", leftImage.c_str(), SDL_GetError());
            }
        }
    }
}

void Character::moveRight()
{
    if (gridX < 31 && !gamePlayground->isPositionBlocked(gridX + 1, gridY))
    {
        gridX++;
        facingRight = true;
        if (!rightImage.empty())
        {
            SDL_Log("Loading character sprite from: %s", rightImage.c_str());
            SDL_Texture *newSprite = loadTexture(rightImage.c_str(), renderer);
            if (newSprite)
            {
                SDL_DestroyTexture(sprite);
                sprite = newSprite;
            }
            else
            {
                SDL_Log("Failed to load character sprite from %s: %s", rightImage.c_str(), SDL_GetError());
            }
        }
    }
}

void Character::moveUp()
{
    if (gridY > 0 && !gamePlayground->isPositionBlocked(gridX, gridY - 1))
    {
        gridY--;
        if (!upImage.empty())
        {
            SDL_Log("Loading character sprite from: %s", upImage.c_str());
            SDL_Texture *newSprite = loadTexture(upImage.c_str(), renderer);
            if (newSprite)
            {
                SDL_DestroyTexture(sprite);
                sprite = newSprite;
            }
            else
            {
                SDL_Log("Failed to load character sprite from %s: %s", upImage.c_str(), SDL_GetError());
            }
        }
    }
}

void Character::moveDown()
{
    if (gridY < 17 && !gamePlayground->isPositionBlocked(gridX, gridY + 1))
    {
        gridY++;
        if (!downImage.empty())
        {
            SDL_Log("Loading character sprite from: %s", downImage.c_str());
            SDL_Texture *newSprite = loadTexture(downImage.c_str(), renderer);
            if (newSprite)
            {
                SDL_DestroyTexture(sprite);
                sprite = newSprite;
            }
            else
            {
                SDL_Log("Failed to load character sprite from %s: %s", downImage.c_str(), SDL_GetError());
            }
        }
    }
}

void Character::setName(const std::string &newName)
{
    name = newName;
    updateNameTexture();
}

void Character::updateNameTexture()
{
    if (nameTexture)
    {
        SDL_DestroyTexture(nameTexture);
        nameTexture = nullptr;
    }

    if (!nameFont)
    {
        SDL_Log("Font not loaded, cannot create name texture");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(nameFont, name.c_str(), nameColor);
    if (!surface)
    {
        SDL_Log("Failed to create name surface: %s", TTF_GetError());
        return;
    }

    nameTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!nameTexture)
    {
        SDL_Log("Failed to create name texture: %s", SDL_GetError());
    }
}

void Character::render()
{
    SDL_Rect destRect = {
        gridX * GRID_SIZE,
        gridY * GRID_SIZE,
        GRID_SIZE,
        GRID_SIZE};

    // Render character sprite
    if (!sprite)
    {
        SDL_Log("Sprite is null, attempting to reload.");
        sprite = loadTexture(downImage.c_str(), renderer); // Attempt to reload image
        if (!sprite)
        {
            SDL_Log("Failed to reload character sprite from %s: %s", downImage.c_str(), SDL_GetError());
        }
    }

    if (sprite)
    {
        SDL_Log("Rendering character sprite.");
        SDL_RenderCopy(renderer, sprite, nullptr, &destRect);
    }
    else
    {
        SDL_Log("Rendering fallback rectangle.");
        // Fallback to colored rectangle if sprite is not loaded
        SDL_SetRenderDrawColor(renderer, clothesColor.r, clothesColor.g, clothesColor.b, clothesColor.a);
        SDL_RenderFillRect(renderer, &destRect);
    }

    // Render name if available
    if (nameTexture)
    {
        int textWidth, textHeight;
        if (SDL_QueryTexture(nameTexture, nullptr, nullptr, &textWidth, &textHeight) == 0)
        {
            SDL_Rect nameRect = {
                destRect.x + (GRID_SIZE - textWidth) / 2,
                destRect.y - textHeight - 5,
                textWidth,
                textHeight};
            SDL_RenderCopy(renderer, nameTexture, nullptr, &nameRect);
        }
    }
}

void Character::update()
{
    // Add any continuous updates here (animations, etc.)
}