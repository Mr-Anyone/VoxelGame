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


static int makeHeightFromNoise(double noise)
{
    // Noise Cap
    double height = (noise  + 1) * 0.5 * ChunkSize;
    return static_cast<int> (height) + 1;
}

void makeTerrain(ChunkCoordinate coordinate, Chunk& chunk)
{
    Block*** blocks {makeBlockMemory()};

    static noise::module::Perlin perlinModule;
    perlinModule.SetSeed(seed);
    perlinModule.SetOctaveCount(8);
    perlinModule.SetFrequency(0.007);
    perlinModule.SetPersistence(0.55);

    utils::NoiseMap heightMap; // creating two-dimensional height map
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(perlinModule);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(ChunkSize, ChunkSize);


    heightMapBuilder.SetBounds(coordinate.first * ChunkSize, (coordinate.first + 1) * ChunkSize + 1, coordinate.second * ChunkSize, (coordinate.second  + 1) * ChunkSize + 1); // Bonds at (2.0, 1.0), (6.0, 5.0) argument format (lower x, upper x, lower y, upper y)
    heightMapBuilder.Build();

    // Creating Chunk For Terrain
    for(int x = 0; x<ChunkSize; ++x)
    {
        for(int z= 0 ; z<ChunkSize; ++z)
        {
            double noise = heightMap.GetValue(x, z);
            int height = makeHeightFromNoise(noise);
            for(int y = 0; y<ChunkSize; ++y)
            {
                // Fill In Water
                if(y < 10)
                {
                    blocks[x][y][z].isActive = true;
                    blocks[x][y][z].type = WATER;
                    continue;
                }
                // Set The Height
                if(y==height)
                {
                    blocks[x][y][z].isActive = true;
                    blocks[x][y][z].type = GRASS;
                    continue;
                }
                else if ( height - 4 <= y  && y < height)
                {
                    blocks[x][y][z].isActive = true;
                    blocks[x][y][z].type = DIRT;
                    continue;
                }
                else if(y < height -4)
                {
                    blocks[x][y][z].isActive = true;
                    blocks[x][y][z].type = STONE;
                    continue;
                }
                else
                {
                    blocks[x][y][z].isActive = false;
                    blocks[x][y][z].type = BRICK;
                    continue;
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
