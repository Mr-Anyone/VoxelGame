#include "chunk.h"
#include <vector>

Chunk::Chunk(Chunk&& chunk)
{
    chunk.m_blocks = m_blocks;
    m_blocks = nullptr; 
    
    chunk.m_xOffset = m_xOffset; 
    chunk.m_yOffset = m_yOffset;
}

Chunk::~Chunk()
{
    if(m_blocks == nullptr)
    {
        return;
    }

    for(int i = 0; i<ChunkSize; ++i)
    {
        for(int x = 0;x<ChunkSize; ++x)
        {
            delete[] m_blocks[i][x];
        }

        delete [] m_blocks[i];
    }
}

Chunk::Chunk(Block***copiedChunk, int xOffset, int yOffset)
{
    m_blocks = new Block**[ChunkSize];

    // Creating and copying memory
    for(int i = 0; i<ChunkSize; ++i)
    {
        m_blocks[i] = new Block* [ChunkSize];
        for(int x = 0; x<ChunkSize; ++x)
        {
            m_blocks[i][x]= new Block [ChunkSize];
            
            // copying memory
            for(int z = 0; z<ChunkSize; ++z)
            {
                m_blocks[i][x][z] = copiedChunk[i][x][z]; 
            }
        }
    }
    m_xOffset = xOffset; 
    m_yOffset = yOffset;
    this->createMesh();
}

void Chunk::createMesh()
{
    std::cout << "Creating Mesh" << std::endl;
}
void Chunk::render(const Shader& shader) const 
{
    std::cout << "Rendering Chunk" << std::endl;
    shader.use(); 
}