#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "block.h"
#include "enemy.h"

namespace leng {
    
const int TILE_WIDTH = 52;

class Level {
public:
    Level(const std::string& fileName);
    ~Level();

        // Getters
    int getWidth() const { return levelData[0].size(); }
    int getHeight() const { return levelData.size(); }

    int levelWidth;
    int levelHeight;

    std::vector<std::string> levelData;
    std::vector<Block*> blocks;
    std::vector<Enemy*> enemies;
    glm::vec2 startPlayerPos;
};

} // namespace leng

#endif // LEVEL_H
