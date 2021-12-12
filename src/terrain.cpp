#include <iostream>
#include <noise/noise.h>
#include <noiseutils.h>

#include "terrain.h"
#include "chunk.h"
#include "chunkManager.h"

// Heap allocated memory, so I could indeed return this
static Block*** makeBlockMemory()
{
    Block*** blocks {new Block** [ChunkSize]}; 
    for(int i = 0; i<ChunkSize; ++i)
    {
        blocks[i] = new Block* [ChunkSize];
        for(int x = 0; x<ChunkSize; ++x)
        {
            blocks[i][x] = new Block[ChunkSize];
        }
    }
    
    return blocks;
}


void makeTerrain(ChunkCoordinate coordinate, Chunk& chunk)
{
    static noise::module::Perlin perlinNoiseModule;
    constexpr double threshold {0.5};
    Block*** blocks {makeBlockMemory()};
    
    // Creating Block Mesh
    for(int x = 0; x<ChunkSize; ++x)
    {
        for(int y = 0; y<ChunkSize; ++y)
        {
            for(int z = 0; z<ChunkSize; ++z)
            {
                double value = perlinNoiseModule.GetValue(0.1 * x, 0.1 * y, 0.1 * z);
                if(value > threshold)
                {
                    blocks[x][y][z].isActive = true;
                }
                else
                {
                    blocks[x][y][z].isActive = false;
                }
            }
        }
    }

    chunk = std::move(Chunk (blocks, coordinate.first, coordinate.second));

    // deallocate block mesh 
    for(int x = 0; x<ChunkSize; ++x)
    {
        for(int i = 0; i<ChunkSize; ++i)
        {
            delete[] blocks[x][i];
        }
        delete[] blocks[x];       
    }
    delete[] blocks;       
}