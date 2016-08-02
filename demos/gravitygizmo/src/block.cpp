#include "block.h"
#include <iostream>

namespace leng {

Block::Block(float x, float y, float width, float height, const std::string& path, BlockType Type) : Entity(x, y, width, height, path), type(Type) { }

Block::~Block() {}
    
} // namespace leng
