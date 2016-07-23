#include <fstream>
#include <iostream>
#include <algorithm>

#include "level.h"

namespace leng {
    
Level::Level(const std::string& fileName) {

    std::ifstream file;
    file.open(fileName);

    // Error checking
    if (file.fail()) {
	std::cout << "Failed to open: " << fileName << std::endl;
    }

    // Throw away the first string in tmp
    std::string tmp;
    file >> tmp;

    std::getline(file, tmp); // Throw away the rest of the first line

    // Read the level data
    while (std::getline(file, tmp)) {
        levelData.emplace_back(tmp);
    }    

	// Level height in pixels
	levelHeight = levelData.size() * TILE_WIDTH;
	// Level width in pixels
	levelWidth = levelData[0].size() * TILE_WIDTH;

	std::cout << "Level height: " << levelHeight << ", width: " << levelWidth << std::endl;

    // The level is flipped, reverse the vector
    std::reverse(levelData.begin(), levelData.end());

    // Render all the tiles
    for (unsigned int y = 0; y < levelData.size(); y++) {
        for (unsigned int x = 0; x < levelData[y].size(); x++) {
            // Grab the tile
            char tile = levelData[y][x];

            // Process the tile
            switch (tile) {
	    case '#': {
		Block* block = new Block(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, "assets/textures/grass_block_52x52.png", BlockType::SOLID);
		blocks.push_back(block);
	    } break;
	    case 'S': {
		Block* block = new Block(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, "assets/textures/spike_bot_52x52.png", BlockType::KILL);
		blocks.push_back(block);
	    } break;
	    case 's': {
		Block* block = new Block(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, "assets/textures/spike_top_52x52.png", BlockType::KILLREVERSE);
		blocks.push_back(block);
	    } break;

	    case '*': {
		Block* block = new Block(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, "assets/textures/exit_block_52x52.png", BlockType::EXIT);
		blocks.push_back(block);
	    } break;
	    case 'X': {
		Block* block = new Block(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, "assets/textures/disappearing_block_52x52.png", BlockType::DISAPPEARING);
		blocks.push_back(block);
	    } break;
	    case 'E': {
		Enemy* enemy = new Enemy(x * TILE_WIDTH, y * TILE_WIDTH, 78, 78, "assets/textures/enemy_black_78x78.png", EnemyType::X_MOVING, glm::fvec2(7.0f, 0.50f));
		enemies.push_back(enemy);
	    } break;
	    case 'M': {
		Enemy* enemy = new Enemy(x * TILE_WIDTH, y * TILE_WIDTH, 78, 78, "assets/textures/enemy_black_78x78.png", EnemyType::X_MOVINGJUMPING, glm::fvec2(5.0f, 0.30f));
		enemies.push_back(enemy);
	    } break;
	    case 'J': {
		Enemy* enemy = new Enemy(x * TILE_WIDTH, y * TILE_WIDTH, 78, 78, "assets/textures/enemy_black_78x78.png", EnemyType::JUMPING, glm::fvec2(0.0f, 0.0f));
		enemies.push_back(enemy);
	    } break;
	    case 'j': {
		Enemy* enemy = new Enemy(x * TILE_WIDTH, y * TILE_WIDTH, 78, 78, "assets/textures/enemy_black_rev_78x78.png", EnemyType::REVERSEJUMPING, glm::fvec2(0.0f, 0.0f));
		enemies.push_back(enemy);
	    } break;
	    case 'f': {
		Enemy* enemy = new Enemy(x * TILE_WIDTH, y * TILE_WIDTH, 78, 78, "assets/textures/enemy_black_78x78.png", EnemyType::STILL, glm::fvec2(0.0f, 0.0f));
		enemies.push_back(enemy);
	    } break;
	    case '@': {
		startPlayerPos.x = (float)x * (float)TILE_WIDTH;
		startPlayerPos.y = (float)y * (float)TILE_WIDTH;
	    } break;
	    case '.':
		break;
	    default: {
		std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
	    } break;
            }
        }
    }
}

Level::~Level()
{
    // Delete the blocks
    for (unsigned int i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }
    // Delete the tiles
    for (unsigned int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
}

}
