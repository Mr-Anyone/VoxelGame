#ifndef CHUNK_H
#define CHUNK_H 

#include <vector>

#include "shader.h"
#include "block.h"
inline constexpr int ChunkSize  {64};
inline constexpr int BlockSize  {1};


enum ChunkFace
{
    up,
    right,
    left,
    down,
    NUM
};

class Chunk
{
    // TO Do: remove is m_isActive as I don't this I will be needing it
public:
    Chunk();
    ~Chunk();
    Chunk(Block***copiedChunk, int xOffset, int zOffset);
    
    // deleating copy constructor
    Chunk(const Chunk&) = delete;
    Chunk& operator=(Chunk& chunk) = delete; 

    // move operator
    Chunk(Chunk&& chunk);
    Chunk& operator=(Chunk&& chunk); 

    void render(Shader& shader) const;
    void setOffset(int xOffset, int zOffset);
    bool IsActive() const;
    void createMesh();
    void setNeighbour(ChunkFace face, Chunk* neighbour);
private:
    bool hasNeighbourOnFourSide(int x, int y, int z);
    void makeBlockMesh(int x, int y, int z);

    int m_zOffset{0}, m_xOffset {0};
    int m_vetReserveSize {300000};
    bool m_isActive {false};
    Block*** m_blocks {nullptr};
    std::vector<float> m_vertices {};
    unsigned int VAO{0}, VBO{0};
    Chunk* m_neighbour[ChunkFace::NUM] {nullptr, nullptr, nullptr, nullptr};
};

void makeTestChunk(Chunk& chunk, int xOffset, int yOffset);

#endif