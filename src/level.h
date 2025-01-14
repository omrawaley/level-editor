#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "tile.h"

struct Level
{
    std::vector<std::vector<Tile>> data;

    void resize(SDL_Renderer* renderer, int width, int height);

    int getWidth();
    int getHeight();
};