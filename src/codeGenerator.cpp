#include "codeGenerator.h"

void CodeGenerator::generateCode(Level& level, std::vector<Tile>& tiles)
{
    std::string enumCode = "enum class TileType\n{\n"; 

    for(auto& tile : tiles)
    {
        enumCode += tile.name + ",\n";
    }

    enumCode += "None,\n";

    enumCode += "};";

    std::string levelCode = "const int " + this->levelName + " [" + std::to_string(level.getHeight()) + "]" + "[" + std::to_string(level.getWidth()) + "]" + "\n{\n";

    for(size_t row = 0; row < level.data.size(); ++row)
    {
        for(size_t col = 0; col < level.data.at(row).size(); ++col)
        {
            levelCode += "TileType::";

            level.data.at(row).at(col).name == "\0" ? levelCode += "None, " : levelCode += level.data.at(row).at(col).name + ", ";
        }

        levelCode += "\n";
    }

    levelCode += "};";

    this->code = enumCode + "\n\n" + levelCode;
}

void CodeGenerator::setLevelName(std::string name)
{
    this->levelName = name;
}

std::string CodeGenerator::getCode()
{
    return this->code;
}