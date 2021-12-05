#include <iostream>
#include <noise/noise.h>

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

static int processValue(double value)
{
    // capping value
    if(value <= -1)
        value = -1; 
    if(value >=1 )
        value = 1;

    return static_cast<int> ((value + 1) * 0.5 * ChunkSize);
}

void makeTerrain(ChunkCoordinate coordinate, Chunk& chunk)
{
    static noise::module::Perlin myModule;
    Block*** blocks {makeBlockMemory()};

    // Creating Block Mesh
    for(int x = 0; x<ChunkSize; ++x)
    {
        for(int z = 0; z<ChunkSize; ++z)
        {
            double value = myModule.GetValue (x + ChunkSize * coordinate.first, 5.1, z + ChunkSize * coordinate.second);
            int processedValue = processValue(value);
            for(int y = 0; y<ChunkSize; ++y)
            {
                if(y <processedValue)
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