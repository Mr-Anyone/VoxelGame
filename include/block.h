#ifndef BLOCK_H
#define BLOCK_H

enum BlockTypes {
    BRICK,
    WATER,
    STONE,
    GRASS,
    DIRT,
    NUMBLOCKTYPE
};

struct Block {
    BlockTypes type;
    bool isActive;
};

#endif
