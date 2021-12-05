#include <vector>
#include <utility>

#include "chunk.h"
#include "camera.h"
#include "shader.h"

extern Camera camera_g;
extern glm::mat4 projection_g;

Chunk::Chunk(Chunk&& chunk)
{
    // self protection 
    if(&chunk == this)
        return; 
    
    std::cout << "Moved Mesh" << std::endl;
    m_blocks = chunk.m_blocks;
    chunk.m_blocks = nullptr; 
    
    m_vertices.swap(chunk.m_vertices);

    m_xOffset = chunk.m_xOffset;
    m_yOffset = chunk.m_yOffset;
    VAO = chunk.VAO;
    VBO = chunk.VBO ;
}

Chunk::~Chunk()
{
    std::cout << "Deallocate Memory" << std::endl;
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
    for(int i = 0; i<sizeof(cubeVertices)/ sizeof(float); i += 3)
    {
        // x, y, z position data
        m_vertices.push_back(cubeVertices[i] + x);
        m_vertices.push_back(cubeVertices[i + 1] + y);
        m_vertices.push_back(cubeVertices[i + 2] + z);
    }
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

    std::cout << "Made Object" << std::endl;
    // Create OpenGL Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0 ); 
    glEnableVertexAttribArray(0);
    std::cout << "Made OpenGL Object" << std::endl;
    std::cout << "Mesh Size: " << m_vertices.size() << std::endl;
    // glBindVertexArray(0);
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

void makeTestChunk(Chunk& chunk)
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
    chunk = std::move(Chunk  (blocks, 0, 0));   
}

Chunk::Chunk()
{
    std::cout << "Created Empty Chunk" << std::endl;
}

Chunk& Chunk::operator=(Chunk&& chunk)
{
    // self protection 
    if(&chunk == this)
        return *this; 
    
    std::cout << "Moved Mesh" << std::endl;
    m_blocks = chunk.m_blocks;
    chunk.m_blocks = nullptr; 
    
    m_vertices.swap(chunk.m_vertices);

    m_xOffset = chunk.m_xOffset;
    m_yOffset = chunk.m_yOffset;
    VAO = chunk.VAO;
    VBO = chunk.VBO ;
    return *this;
}