#ifndef BLOCK_H
#define BLOCK_H

#include "entity.h"

namespace leng {

enum BlockType {
    SOLID,
    KILL,
    KILLREVERSE,
    DISAPPEARING,
    EXIT
};
    
class Block : public Entity {
public:
    Block(float x, float y, float width, float height, const std::string& path, BlockType Type);
    ~Block();

    BlockType type;
};

} // namespace leng

#endif // BLOCK_H
