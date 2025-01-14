#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "tile.h"
#include "level.h"
#include "camera.h"
#include "codeGenerator.h"
#include "gui.h"

class Editor
{
    private:
        const Uint8* keys;

        SDL_Window* window;
        SDL_Renderer* renderer;

    private:
        std::vector<Tile> tiles;

        int* selectedTileId;

        Level level;

        Camera camera;

        CodeGenerator codeGenerator;

    private:
        void loadMedia();
        void freeMedia();

    public:
        bool quit;

    public:
        Editor();
        ~Editor();

        void start();
        void eventLoop();
        void update();
        void draw();
};
