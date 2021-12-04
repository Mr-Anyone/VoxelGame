#ifndef CHUNK_H
#define CHUNK_H 

#include "shader.h"
inline constexpr int ChunkSize  {16};
inline constexpr int BlockSize  {1};

enum BlockTypes 
{
    BLOCKAIR, 
    WHITE,
    NUMBLOCKTYPE
};

struct Block 
{
    BlockTypes type;
    bool isActive;
};

class Chunk
{
public:
    ~Chunk();
    Chunk(Block***copiedChunk, int xOffset, int yOffset);

    Chunk(const Chunk& chunk) = delete;
    Chunk(Chunk&& chunk);

    void render(const Shader& shader) const;
private:
    void createMesh();

    Block*** m_blocks;
    int m_xOffset, m_yOffset;
};

#endif