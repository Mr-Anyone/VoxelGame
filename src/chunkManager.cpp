#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <stbi_image.h>

#include "chunk.h"
#include "chunkManager.h"
#include "terrain.h"

ChunkManager::ChunkManager()
    : m_renderDistance(2) 
{
    // Assumes the player is at 0, 0
    // Generating chunks for the player 
    for(int x = -m_renderDistance; x<m_renderDistance + 1; ++x)
    {
        for(int z = -m_renderDistance; z<m_renderDistance + 1; ++z)
        {
            // Creating Chunk 
            ChunkCoordinate coordinate = std::make_pair(x, z);
            makeNewChunk(coordinate);
        }
    }
    
    this->loadTexture();
}

static bool existInMap(ChunkCoordinate coordinate, const std::map<ChunkCoordinate, Chunk>& map)
{
    if(map.find(coordinate) == map.end())
        return false; 
    
    return true;
}

// Steps to render: 
// Translate player coordinate into chunk coordinate
// Check if the chunk exists, if not create new chunk 
// Render all the chunk within render distance
void ChunkManager::render(Shader& shader, const glm::vec3& playerPos)
{
    ChunkCoordinate coordinate  = std::make_pair(playerPos.x / ChunkSize, playerPos.z/ChunkSize); 
    for(int x = coordinate.first - m_renderDistance; x<m_renderDistance + coordinate.first + 1; ++x)
    {
        for(int z = coordinate.second - m_renderDistance ; z<m_renderDistance + coordinate.second + 1; ++z)
        {
            // Check to see if chunk exists
            ChunkCoordinate renderCoordinate  = std::make_pair(x, z);
            if(!existInMap(renderCoordinate, m_chunks))  
                makeNewChunk(renderCoordinate);
        
            // Render chunk 
            m_chunks.at(renderCoordinate).render(shader); 
        }
    }
}   

void ChunkManager::makeNewChunk(ChunkCoordinate coordinate)
{
    Chunk chunk; 
    makeTerrain(coordinate, chunk);

    m_chunks[coordinate] = std::move(chunk);
}

void ChunkManager::setRenderDistance(int renderDistance)
{
    m_renderDistance = renderDistance;
}

void ChunkManager::loadTexture()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./../res/texture/brickwall.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}