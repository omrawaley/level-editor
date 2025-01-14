#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "level.h"
#include "codeGenerator.h"

namespace GUI
{
    void init(SDL_Window* window, SDL_Renderer* renderer);

    void free();

    void processEvent(SDL_Event& event);

    void showTileEditor(SDL_Renderer* renderer, std::vector<Tile>& tiles, int*& selectedTile);

    void showLevelSettings(SDL_Renderer* renderer, Level& level);

    void showCodeGeneratorSettings(Level& level, CodeGenerator& codeGenerator, std::vector<Tile>& tiles);

    void draw(SDL_Renderer* renderer, std::vector<Tile>& tiles, Level& level, int*& selectedTile, CodeGenerator& codeGenerator);
}