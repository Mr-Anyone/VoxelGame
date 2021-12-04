#include <vector>
#include <utility>

#include "chunk.h"

Chunk::Chunk(Chunk&& chunk)
{
    std::cout << "Moved Mesh" << std::endl;
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

void Chunk::makeBlockMesh(int x, int y, int z)
{
    // std::cout << "Making BlocK Mesh"
}

void Chunk::createMesh()
{
    std::cout << "Creating Mesh" << std::endl;
    for(int x = 0 ; x<ChunkSize; ++x)
    {
        for(int y = 0; y<ChunkSize; ++y)
        {
            for(int z = 0 ; z<ChunkSize; ++z)
            {

                if(!m_blocks[x][y][z].isActive)
                    continue;
                makeBlockMesh(x, y, z);
            }
        }
    }

    // Create OpenGL Object
}

void Chunk::render(const Shader& shader) const 
{
    std::cout << "Rendering Chunk" << std::endl;
    shader.use(); 
}

Chunk&& makeTestChunk()
{
    // allocating memory for block
    Block*** blocks {new Block** [ChunkSize]}; 
    for(int i = 0; i<ChunkSize; ++i)
    {
        blocks[i] = new Block* [ChunkSize]; 
        for(int x = 0; x<ChunkSize; ++x)
        {
            blocks[i][x] = new Block[ChunkSize];
        }
    }

    // set the entire chunk as a huge block
    for(int x = 0; x<ChunkSize; ++x)
    {
        for(int y = 0; y<ChunkSize; ++y)
        {
            for(int z = 0; z<ChunkSize; ++z)
            {
                blocks[x][y][z].isActive = true;
                blocks[x][y][z].type = WHITE;
            }
        }
    }

    //deallocate memory
    return std::move(Chunk (blocks, 0, 0));
}