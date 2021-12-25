#ifndef BLOCK_H
#define BLOCK_H

enum BlockTypes {
    BRICK,
    WATER,
    NUMBLOCKTYPE
};

struct Block {
    BlockTypes type;
    bool isActive;
};

#endif
