#ifndef BLOCK_H
#define BLOCK_H

namespace leng {
    
enum BlockType {
    BlockType_Default = 0,

    BlockType_Grass,
    BlockType_Dirt,
    BlockType_Water,
    BlockType_Stone,
    BlockType_Wood,
    BlockType_Sand,

    BlockType_NumTypes
};

class Block {
public:
    Block();
    ~Block();

    bool isActive();
    void setActive(bool Active);

private:
    bool active {true};

    BlockType blockType;
};

} // namespace leng

#endif // BLOCK_H
