#include "editor.h"

Editor::Editor() : quit(false), keys(nullptr), window(nullptr), renderer(nullptr), selectedTileId(nullptr)
{
    this->loadMedia();
}

Editor::~Editor()
{
    this->freeMedia();
}

void Editor::loadMedia()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_PNG);

	this->window = SDL_CreateWindow("C++ Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GUI::init(this->window, this->renderer);
}

void Editor::freeMedia()
{
    SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
    IMG_Quit();
}

void Editor::start()
{
    this->level.resize(this->renderer, 20, 20);
}

void Editor::eventLoop()
{
    SDL_Event event;
	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				this->quit = true;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						this->quit = true;
						break;

                    case SDLK_m:
                        if(!GUI::active)
                            GUI::show = !GUI::show;
                        break;
                }
				break;
		}

        GUI::processEvent(event);
	}
}

void Editor::update()
{
    this->keys = SDL_GetKeyboardState(nullptr);

    int x, y;

    int gridX, gridY;

    SDL_GetMouseState(&x, &y);

    gridX = (x + this->camera.x) / 32;
    gridY = (y + this->camera.y) / 32;

    if(!GUI::active)
    {

    if(this->keys[SDL_SCANCODE_SPACE] && this->selectedTileId != nullptr && gridX < this->level.getWidth() && gridY < this->level.getHeight())
    {
        this->level.data.at(gridY).at(gridX) = this->tiles.at(*this->selectedTileId);
    }

    if(this->keys[SDL_SCANCODE_W])
    {
        this->camera.y -= 1;
    }

    if(this->keys[SDL_SCANCODE_S])
    {
        this->camera.y += 1;
    }

    if(this->keys[SDL_SCANCODE_A])
    {
        this->camera.x -= 1;
    }

    if(this->keys[SDL_SCANCODE_D])
    {
        this->camera.x += 1;
    }
    }
}

void Editor::draw()
{
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(this->renderer, 50, 50, 50, 50);

    for(size_t row = 0; row < this->level.data.size(); ++row)
    {
        for(size_t col = 0; col < this->level.data.at(row).size(); ++col)
        {
            Tile& tile = this->level.data.at(row).at(col);

            SDL_Rect rect = SDL_Rect {(static_cast<int>(col) * 32) - this->camera.x, (static_cast<int>(row) * 32) - this->camera.y, 32, 32};

            SDL_RenderCopy(this->renderer, tile.texture, nullptr, &rect);
        }
    }

    GUI::draw(this->renderer, this->tiles, this->level, this->selectedTileId, this->codeGenerator);

    SDL_RenderPresent(this->renderer);
}
