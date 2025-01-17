#include "level.h"

void Level::resize(SDL_Renderer* renderer, int width, int height)
{
    this->data.clear();

    SDL_Texture* frameTexture = IMG_LoadTexture(renderer, "assets/EmptyFrame.png");

    for(size_t row = 0; row < height; ++row)
    {
        std::vector<Tile> rowTiles;

        for(size_t col = 0; col < width; ++col)
        {
            rowTiles.push_back(Tile{"", -1, frameTexture});
        }

        this->data.push_back(rowTiles);
    }
};

int Level::getWidth()
{
    return this->data.front().size();
}

int Level::getHeight()
{
    return this->data.size();
}