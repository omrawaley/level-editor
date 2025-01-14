#pragma once

#include <SDL2/SDL.h>
#include <string>

struct Tile
{
    std::string name;
    int id;
    SDL_Texture* texture;
};