#ifndef TERRAIN_H 
#define TERRAIN_H 

#include "terrain.h"
#include "chunk.h"
#include "chunkManager.h"

constexpr int seed = 10;
void makeTerrain(ChunkCoordinate coordinate, Chunk& chunk);
void makeNoiseMap(ChunkCoordinate coordinate, Chunk& chunk);
#endif