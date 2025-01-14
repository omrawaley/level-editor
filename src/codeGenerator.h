#pragma once

#include <string>

#include "level.h"

class CodeGenerator
{
    private:
        std::string levelName;

        std::string code;

    public:
        void generateCode(Level& level, std::vector<Tile>& tiles);

        void setLevelName(std::string name);

        std::string getCode();
};