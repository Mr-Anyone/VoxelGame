#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "chunk.h"
#include "chunkManager.h"

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
    makeTestChunk(chunk, coordinate.first, coordinate.second);

    m_chunks[coordinate] = std::move(chunk);
}

void ChunkManager::setRenderDistance(int renderDistance)
{
    m_renderDistance = renderDistance;
}