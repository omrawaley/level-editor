#include "gui.h"

#include <SDL2/SDL_image.h>

#include "../deps/imgui/imgui.h"
#include "../deps/imgui/imfilebrowser.h"
#include "../deps/imgui/backends/imgui_impl_sdl2.h"
#include "../deps/imgui/backends/imgui_impl_sdlrenderer2.h"

bool GUI::show = true;
bool GUI::active = false;

void GUI::init(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void GUI::free()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUI::processEvent(SDL_Event& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void GUI::showTileEditor(SDL_Renderer* renderer, std::vector<Tile>& tiles, int*& selectedTileId)
{
    ImGui::SetNextWindowSize(ImVec2{320, 600});

    ImGui::SetNextWindowPos(ImVec2{960, 0});

    ImGui::Begin("Tile Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    static ImGui::FileBrowser fileDialog {ImGuiFileBrowserFlags_EditPathString};

    fileDialog.SetTitle("select tile image");
    fileDialog.SetTypeFilters({".png", ".bmp", ".jpg", ".jpeg"});

    for(size_t i = 0; i < tiles.size(); ++i)
    {
        ImGui::PushID(i);

        ImGui::Text("%s", tiles.at(i).name.c_str());
        ImGui::Text("%d", tiles.at(i).id);

        ImGui::Image(tiles.at(i).texture, ImVec2{50, 50});

        if(ImGui::Button("Select"))
        {
            selectedTileId = &tiles.at(i).id;
        }

        ImGui::Separator();

        ImGui::PopID();
    }

    static char newTileName[32];

    ImGui::InputText("New Tile Name", newTileName, IM_ARRAYSIZE(newTileName));

    static SDL_Texture* newTileTexture;

    ImGui::Image(newTileTexture, ImVec2{50, 50});

    if(ImGui::Button("New Tile Image"))
    {
        fileDialog.Open();
    }

    if(ImGui::Button("Add Tile"))
    {
        tiles.push_back(Tile{newTileName, static_cast<int>(tiles.size()), newTileTexture});

        memset(newTileName, '\0', sizeof(newTileName));

        newTileTexture = nullptr;
    }

    ImGui::End();

    fileDialog.Display();

    if(fileDialog.HasSelected())
    {
        newTileTexture = IMG_LoadTexture(renderer, fileDialog.GetSelected().c_str());

        fileDialog.ClearSelected();
    }
}

void GUI::showLevelSettings(SDL_Renderer* renderer, Level& level)
{
    ImGui::SetNextWindowSize(ImVec2{320, 150});

    ImGui::SetNextWindowPos(ImVec2{960, 570});

    ImGui::Begin("Level Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    static int levelWidth;
    static int levelHeight;

    ImGui::InputInt("Level Width", &levelWidth);
    ImGui::InputInt("Level Height", &levelHeight);

    if(ImGui::Button("Clear & Resize Level"))
    {
        level.resize(renderer, levelWidth, levelHeight);
    }

    ImGui::End();
}

void GUI::showCodeGeneratorSettings(Level& level, CodeGenerator& codeGenerator, std::vector<Tile>& tiles)
{
    ImGui::SetNextWindowSize(ImVec2{960, 150});

    ImGui::SetNextWindowPos(ImVec2{0, 570});

    ImGui::Begin("Code Generator", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    static char levelName[32];

    ImGui::InputText("Level Name", levelName, IM_ARRAYSIZE(levelName));

    if(ImGui::Button("Apply"))
    {
        codeGenerator.setLevelName(levelName);
    }

    static char code[4096];

    if(ImGui::Button("Generate Code"))
    {
        codeGenerator.generateCode(level, tiles);
    }

    if(ImGui::Button("Copy Code"))
    {
        ImGui::SetClipboardText(codeGenerator.getCode().c_str());
    }

    ImGui::InputTextMultiline("##codeblock", const_cast<char*>(codeGenerator.getCode().c_str()), sizeof(codeGenerator.getCode()), ImVec2(-FLT_MIN, 200), ImGuiInputTextFlags_ReadOnly);

    ImGui::End();
}

void GUI::draw(SDL_Renderer* renderer, std::vector<Tile>& tiles, Level& level, int*& selectedTile, CodeGenerator& codeGenerator)
{
    if(!GUI::show)
        return;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    GUI::active = ImGui::IsAnyItemActive() ? true : false;

    GUI::showTileEditor(renderer, tiles, selectedTile);

    GUI::showLevelSettings(renderer, level);

    GUI::showCodeGeneratorSettings(level, codeGenerator, tiles);

    ImGui::Render();

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}