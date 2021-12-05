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
    Chunk();
    ~Chunk();
    Chunk(Block***copiedChunk, int xOffset, int yOffset);
    
    // deleating copy constructor
    Chunk(const Chunk&) = delete;
    Chunk& operator=(Chunk& chunk) = delete; 

    // move operator
    Chunk(Chunk&& chunk);
    Chunk& operator=(Chunk&& chunk); 

    void render(Shader& shader) const;
private:
    void makeBlockMesh(int x, int y, int z);
    void createMesh();

    int m_yOffset, m_xOffset;
    Block*** m_blocks {nullptr};
    std::vector<float> m_vertices {};
    unsigned int VAO, VBO;
};

void makeTestChunk(Chunk& chunk);

static float cubeVertices[] = {
    -1.0f, -1.0f, -1.0f,  
    1.0f, -1.0f, -1.0f,  
    1.0f,  1.0f, -1.0f,  
    1.0f,  1.0f, -1.0f,  
    -1.0f,  1.0f, -1.0f,  
    -1.0f, -1.0f, -1.0f,  

    -1.0f, -1.0f,  1.0f,  
    1.0f, -1.0f,  1.0f,  
    1.0f,  1.0f,  1.0f,  
    1.0f,  1.0f,  1.0f,  
    -1.0f,  1.0f,  1.0f,  
    -1.0f, -1.0f,  1.0f,  

    -1.0f,  1.0f,  1.0f,  
    -1.0f,  1.0f, -1.0f,  
    -1.0f, -1.0f, -1.0f,  
    -1.0f, -1.0f, -1.0f,  
    -1.0f, -1.0f,  1.0f,  
    -1.0f,  1.0f,  1.0f,  

    1.0f,  1.0f,  1.0f,  
    1.0f,  1.0f, -1.0f,  
    1.0f, -1.0f, -1.0f,  
    1.0f, -1.0f, -1.0f,  
    1.0f, -1.0f,  1.0f,  
    1.0f,  1.0f,  1.0f,  

    -1.0f, -1.0f, -1.0f,  
    1.0f, -1.0f, -1.0f,  
    1.0f, -1.0f,  1.0f,  
    1.0f, -1.0f,  1.0f,  
    -1.0f, -1.0f,  1.0f,  
    -1.0f, -1.0f, -1.0f,  

    -1.0f,  1.0f, -1.0f,  
    1.0f,  1.0f, -1.0f,  
    1.0f,  1.0f,  1.0f,  
    1.0f,  1.0f,  1.0f,  
    -1.0f,  1.0f,  1.0f,  
    -1.0f,  1.0f, -1.0f
};

#endif