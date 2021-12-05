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
            Chunk chunk;
            makeTestChunk(chunk, x, z); 

            // Storing Chunk 
            ChunkCoordinate coordinate = std::make_pair(x, z);
            m_chunks[coordinate] = std::move(chunk);
        }
    }
}

void ChunkManager::render(Shader& shader, const glm::vec3& playerPos) const
{
    for(int x = -m_renderDistance; x<m_renderDistance + 1; ++x)
    {
        for(int y = -m_renderDistance; y<m_renderDistance + 1; ++y)
        {
            ChunkCoordinate coordinate = std::make_pair(x, y); 
        }
    }
}