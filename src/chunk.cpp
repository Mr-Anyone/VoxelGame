#include <vector>
#include <utility>

#include "chunk.h"
#include "camera.h"
#include "chunkManager.h"
#include "shader.h"

extern Camera camera_g;
extern glm::mat4 projection_g;

Chunk::Chunk(Chunk&& chunk)
{
    // self protection 
    if(&chunk == this)
        return; 
    
    m_blocks = chunk.m_blocks;
    chunk.m_blocks = nullptr; 
    
    m_vertices.swap(chunk.m_vertices);

    m_xOffset = chunk.m_xOffset;
    m_isActive = chunk.m_isActive;
    m_zOffset = chunk.m_zOffset;
    VAO = chunk.VAO;
    VBO = chunk.VBO ;
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

Chunk::Chunk(Block***copiedChunk, int xOffset, int zOffset): 
    m_xOffset {xOffset}, m_zOffset{zOffset}, m_isActive{true}
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
    this->createMesh();
}

void Chunk::makeBlockMesh(int x, int y, int z)
{
    for(int i = 0; i<sizeof(cubeVertices)/ sizeof(float); i += 5)
    {
        // x, y, z position data
        m_vertices.push_back(cubeVertices[i] + x + m_xOffset * ChunkSize);
        m_vertices.push_back(cubeVertices[i + 1] + y);
        m_vertices.push_back(cubeVertices[i + 2] + z + m_zOffset * ChunkSize);
        // textures informations
        m_vertices.push_back(cubeVertices[i+ 3]);
        m_vertices.push_back(cubeVertices[i+ 4]);

    }
}

void Chunk::createMesh()
{
    for(int x = 0 ; x<ChunkSize; ++x)
    {
        for(int y = 0; y<ChunkSize; ++y)
        {
            for(int z = 0 ; z<ChunkSize; ++z)
            {
                if(hasNeighbourOnFourSide(x, y, z))
                    continue;
                
                if(!m_blocks[x][y][z].isActive)
                    continue;
                makeBlockMesh(x, y, z);
            }
        }
    }

    // Create OpenGL Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0 ); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 3)); 
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Chunk::render(Shader& shader) const 
{
    shader.use(); 
    glBindVertexArray(VAO); 
    shader.setMat4("view", camera_g.getView());
    shader.setMat4("model", glm::mat4 (1.0f));
    shader.setMat4("projection", projection_g);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void makeTestChunk(Chunk& chunk, int xOffset, int zOffset)
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
    // Make Chunk
    chunk = std::move(Chunk  (blocks, xOffset, zOffset));   
    
    // deallocate memory for blocks 
}

Chunk::Chunk(): 
    m_isActive {false}
{
}

Chunk& Chunk::operator=(Chunk&& chunk)
{
    // self protection 
    if(&chunk == this)
        return *this; 
    
    m_blocks = chunk.m_blocks;
    chunk.m_blocks = nullptr; 
    
    m_vertices.swap(chunk.m_vertices);

    m_xOffset = chunk.m_xOffset;
    m_zOffset = chunk.m_zOffset;
    VAO = chunk.VAO;
    VBO = chunk.VBO ;
    return *this;
}

bool Chunk::hasNeighbourOnFourSide(int x, int y, int z)
{
    // re-write this code. What is this copying code shit! 

    for(int yy = -1; yy<2; ++yy)
    {
        int compareY = y + yy; 
        // at a edge
        if(compareY < 0 || compareY >= ChunkSize)
        {
            return false;
        }
        // check to see if neighbour exists
        if(!m_blocks[x][compareY][z].isActive)
        {
            return false;
        }
    }
    
    for(int xx = -1; xx<2; ++xx)
    {
        int compareX = x + xx; 
        // at a edge
        if(compareX < 0 || compareX >= ChunkSize)
        {
            return false;
        }
        // check to see if neighbour exists
        else
        {
            if(!m_blocks[compareX][y][z].isActive)
            {
                return false;
            }
        }
    }

    for(int zz = -1; zz<2; ++zz)
    {
        int compareZ = z + zz; 
        // at a edge
        if(compareZ < 0 || compareZ >= ChunkSize)
        {
            return false;
        }
        // check to see if neighbour exists
        else
        {
            if(!m_blocks[x][y][compareZ].isActive)
            {
                return false;
            }
        }
    }
    return true;
}

void Chunk::setOffset(int xOffset, int zOffset) 
{
    m_xOffset = xOffset; 
    m_zOffset = zOffset;
}

bool Chunk::IsActive() const 
{
    return m_isActive;
}