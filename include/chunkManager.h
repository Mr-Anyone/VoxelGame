#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H 

#include <map>
#include <utility>
#include <glm/glm.hpp>

#include "chunk.h"
#include "shader.h"

typedef std::pair<int, int> ChunkCoordinate;

class ChunkManager
{ 
    std::map<ChunkCoordinate, Chunk> m_chunks {};
    int m_renderDistance;
    unsigned int m_texture;
    
    void makeNewChunk(ChunkCoordinate coordinate);
    void loadTexture();
public:
    ChunkManager();
    void render(Shader& shader, const glm::vec3& playerPos);
    void setRenderDistance(int renderDistance);
}; 

#endif