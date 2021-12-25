#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stbi_image.h>

#include "chunk.h"
#include "chunkManager.h"
#include "terrain.h"

static bool existInMap(ChunkCoordinate coordinate, const std::map<ChunkCoordinate, Chunk>& map)
{
    auto it = map.find(coordinate);
    return it != map.end();
}

void ChunkManager::addNeighbour(ChunkCoordinate coordinate, bool createMesh)
{
    if(!existInMap(coordinate, m_chunks))
    {
        return;
    }

    // left side
    if(existInMap({coordinate.first - 1 , coordinate.second}, m_chunks))
        m_chunks[coordinate].setNeighbour(ChunkFace::left, &m_chunks[{coordinate.first -1, coordinate.second}]);

    // right side
    if(existInMap({coordinate.first + 1 , coordinate.second}, m_chunks))
        m_chunks[coordinate].setNeighbour(ChunkFace::right, &m_chunks[{coordinate.first + 1, coordinate.second}]);

    // up-side
    if(existInMap({coordinate.first , coordinate.second + 1}, m_chunks))
        m_chunks[coordinate].setNeighbour(ChunkFace::up, &m_chunks[{coordinate.first , coordinate.second + 1}]);
    // down-side
    if(existInMap({coordinate.first , coordinate.second - 1}, m_chunks))
        m_chunks[coordinate].setNeighbour(ChunkFace::down, &m_chunks[{coordinate.first , coordinate.second - 1 }]);

    if(createMesh)
        m_chunks[coordinate].createMesh();
}

ChunkManager::ChunkManager()
    : m_renderDistance(2), m_texture {0}
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

    // Creates Chunk Mesh
    for(int x = -m_renderDistance; x<m_renderDistance +1; ++x)
    {
        for(int z = -m_renderDistance; z < m_renderDistance + 1; ++z)
        {
            ChunkCoordinate coordinate = std::make_pair(x, z);
            addNeighbour(coordinate);
        }
    }
    this->loadTexture();
}

inline static void addNeighbourChunkVet(std::vector<ChunkCoordinate>& vet, ChunkCoordinate coordinate)
{
    vet.emplace_back(coordinate.first, coordinate.second);
    vet.emplace_back(coordinate.first + 1, coordinate.second);
    vet.emplace_back(coordinate.first - 1, coordinate.second);
    vet.emplace_back(coordinate.first , coordinate.second + 1);
    vet.emplace_back(coordinate.first , coordinate.second - 1);
}

void ChunkManager::render_init(ChunkCoordinate coordinate)
{
    // Creating Chunk Mesh
    std::vector<ChunkCoordinate> newChunks {};
    for(int i = coordinate.first - m_renderDistance; i<m_renderDistance + coordinate.first + 1; ++i)
    {
        for(int z = coordinate.second - m_renderDistance; z< m_renderDistance + coordinate.second + 1; ++z)
        {
            ChunkCoordinate newChunk = std::make_pair(i, z);
            if(existInMap(newChunk, m_chunks))
            {
                continue;
            }

            // New Chunks to be created + re-creates neighbour mesh
            Chunk chunk;
            makeTerrain(newChunk, chunk);
            m_chunks[newChunk] = std::move(chunk);
            addNeighbourChunkVet(newChunks, newChunk);
        }
    }

    // Check for neighbour
    for(auto& ele: newChunks)
    {
        addNeighbour(ele, false);
    }
    for(auto&ele : newChunks)
    {
        if(existInMap(ele, m_chunks))
        {
            m_chunks[ele].createMesh();
        }
    }
}

// Steps to render:
// Translate player coordinate into chunk coordinate
// Check if the chunk exists, if not create block data and chunk class
// After all the chunks are created, create chunk mesh
// Render all the chunk within render distance
void ChunkManager::render(Shader& shader, const glm::vec3& playerPos)
{
    ChunkCoordinate coordinate  = std::make_pair(playerPos.x / ChunkSize, playerPos.z/ChunkSize);
    this->render_init(coordinate);

    for(int x = coordinate.first - m_renderDistance; x<m_renderDistance + coordinate.first + 1; ++x)
    {
        for(int z = coordinate.second - m_renderDistance ; z<m_renderDistance + coordinate.second + 1; ++z)
        {
            ChunkCoordinate renderCoordinate  = std::make_pair(x, z);

            // Render chunk
            m_chunks[renderCoordinate].render(shader);
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./../res/texture/Texture-Atlas.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}