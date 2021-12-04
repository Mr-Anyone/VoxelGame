#ifndef CHUNK_H
#define CHUNK_H 

#include <vector>

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
    Chunk() = delete;
    ~Chunk();
    Chunk(Block***copiedChunk, int xOffset, int yOffset);
    
    // deleating copy constructor
    Chunk(const Chunk&) = delete;
    Chunk& operator=(Chunk&) = delete;


    Chunk(Chunk&& chunk);

    void render(const Shader& shader) const;
private:
    void makeBlockMesh(int x, int y, int z);
    void createMesh();

    int m_yOffset, m_xOffset;
    Block*** m_blocks;
    std::vector<float> m_vertices {};
};

Chunk&& makeTestChunk();
#endif