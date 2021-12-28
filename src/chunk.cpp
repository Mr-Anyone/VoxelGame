#include <vector>
#include <utility>

#include "chunk.h"
#include "camera.h"
#include "chunkManager.h"
#include "shader.h"
#include "cubeVertices.h"

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
    m_vertices.reserve(m_vetReserveSize);
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
}

static void pushBackVertices(std::vector<float>& vertices, float* cubeVertices, std::size_t size, int x, int y, int z, int xOffest, int zOffset, BlockTypes blockType, BlockFaceTexture blockFace)
{
    auto it = vertices.end();
    std::size_t verticesSize {vertices.size()};
    vertices.insert(it, cubeVertices, cubeVertices + size);

    // Calculate Vertices Offset
    for(int i = verticesSize; i<verticesSize + size; i += 6)
    {
        vertices[i] = vertices[i] + x + xOffest * ChunkSize;
        vertices[i + 1] = vertices[i + 1] + y;
        vertices[i + 2] = vertices[i + 2] + z + zOffset * ChunkSize ;

        // texture
        int textureFace = static_cast<int> (vertices[i + 3]);
        vertices[i + 3] = textureCoordinateLookup[blockType][blockFace][textureFace][0];
        vertices[i + 4] = textureCoordinateLookup[blockType][blockFace][textureFace][1];
    }
}

// FOR ATTENTION PURPOSES
// FOR ATTENTION PURPOSES
// PLEASE clean this code up !!!!
// FOR ATTENTION PURPOSES
// FOR ATTENTION PURPOSES
void Chunk::makeBlockMesh(int x, int y, int z)
{
    // This would render the edge of the chunk
    if( y + 1 >= ChunkSize)
    
    // the top block face
    {
        pushBackVertices(m_vertices, topFaceCubeVertices, sizeof(topFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::TOP);
    }
    else if(!m_blocks[x][y + 1][z].isActive)
    {
        pushBackVertices(m_vertices, topFaceCubeVertices, sizeof(topFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::TOP);
    }
    
    // bottom block face
    if(y - 1 < 0)
    {
        pushBackVertices(m_vertices, bottomFaceCubeVertices, sizeof(bottomFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::BOTTOM);
    }
    else if(!m_blocks[x][y - 1][z].isActive )
    {
        pushBackVertices(m_vertices, bottomFaceCubeVertices, sizeof(bottomFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::BOTTOM);
    }
    
    // right block face
    if(x +1 >=ChunkSize) // at the edge
    {
        // does the neighbour chunk exists
        if(m_neighbour[ChunkFace::right] == nullptr )
        {
            pushBackVertices(m_vertices, rightFaceCubeVertices, sizeof(rightFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::RIGHT);
        }
        // does neighbour block in other chunk exist
        else if (!m_neighbour[ChunkFace::right]->m_blocks[0][y][z].isActive)
        {
            pushBackVertices(m_vertices, rightFaceCubeVertices, sizeof(rightFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::RIGHT);
        }

    }
    else if(!m_blocks[x + 1][y][z].isActive)
    {
        pushBackVertices(m_vertices, rightFaceCubeVertices, sizeof(rightFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::RIGHT);
    }
    
    // left block face 
    if( x - 1 < 0 )
    {
        if(m_neighbour[ChunkFace::left] == nullptr)
        {
            pushBackVertices(m_vertices, leftFaceCubeVertices, sizeof(leftFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::LEFT);
        }
        else if(!m_neighbour[ChunkFace::left]->m_blocks[ChunkSize - 1][y][z].isActive)
        {
            pushBackVertices(m_vertices, leftFaceCubeVertices, sizeof(leftFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::LEFT);
        }
    }
    else if(!m_blocks[x - 1][y][z].isActive )
    {
        pushBackVertices(m_vertices, leftFaceCubeVertices, sizeof(leftFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::LEFT);
    }

    // Back
    if(z -1 < 0)
    {
        if(m_neighbour[ChunkFace::down] == nullptr)
        {
            pushBackVertices(m_vertices, backFaceCubeVertices, sizeof(backFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::BACK);
        }
        else if(!m_neighbour[ChunkFace::down]->m_blocks[x][y][ChunkSize -1].isActive)
        {
            pushBackVertices(m_vertices, backFaceCubeVertices, sizeof(backFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::BACK);
        }
    }
    else if(!m_blocks[x][y][z - 1].isActive)
    {
        pushBackVertices(m_vertices, backFaceCubeVertices, sizeof(backFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::BACK);
    }

    // Front
    if(z + 1 >= ChunkSize)
    {
        if(m_neighbour[ChunkFace::up] == nullptr)
        {
            pushBackVertices(m_vertices, frontFaceCubeVertices, sizeof(frontFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::FRONT);
        }
        else if(!m_neighbour[ChunkFace::up]->m_blocks[x][y][0].isActive)
        {
            pushBackVertices(m_vertices, frontFaceCubeVertices, sizeof(frontFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::FRONT);
        }
    }
    else if(!m_blocks[x][y][z + 1].isActive )
    {
        pushBackVertices(m_vertices, frontFaceCubeVertices, sizeof(frontFaceCubeVertices) / sizeof(float), x, y, z, m_xOffset, m_zOffset, m_blocks[x][y][z].type, BlockFaceTexture::FRONT);
    }
}

void Chunk::createMesh()
{
    m_vertices.erase(m_vertices.begin(), m_vertices.end());
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
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) (sizeof(float) * 5));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    m_vertices.shrink_to_fit(); // release extra space
}

void Chunk::render(Shader& shader) const 
{
    shader.use(); 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
                blocks[x][y][z].type = BRICK;
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

void Chunk::setNeighbour(ChunkFace face, Chunk* neighbour)
{
    m_neighbour[face] = neighbour;
}