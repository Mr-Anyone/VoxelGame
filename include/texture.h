#ifndef TEXTURE_H
#define TEXTURE_H

#include "block.h"

// Textures for block faces
enum BlockFaceTexture {
    FRONT,
    BACK,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

enum TextureCoordinate {
    topLeft,
    topRight,
    bottomLeft,
    bottomRight,
};

// Texture Lookup

// Texture Coordinate
// Organized as follows [block_type][block_face][corner] -> texture coordinate
static float textureCoordinateLookup[5][6][4][2]
        {
                // brick
                {
// front

                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        },
// back
                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        },
// top
                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        },
// bottom
                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        },
// left
                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        },
// right
                        {
                                {0.0f, 1.0f}, // top left
                                {0.1f, 1.0f}, // top right
                                {0.0f, 0.9f}, // bottom left
                                {0.1f, 0.9f}, // bottom right
                        }
                },
                // water
                {
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                        {
                                {0.1f, 1.0f}, // top left
                                {0.2f, 1.0f}, // top right
                                {0.1f, 0.9f}, // bottom left
                                {0.2f, 0.9f}, // bottom right
                        },
                },
                // Stone
                {
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                        {
                                {0.2f, 1.0f}, // top left
                                {0.3f, 1.0f}, // top right
                                {0.2f, 0.9f}, // bottom left
                                {0.3,  0.9f}, // bottom right
                        },
                },
                // Grass
                {
                        {
                                {0.4f, 1.0f}, // top left
                                {0.5f, 1.0f}, // top right
                                {0.4f, 0.9f}, // bottom left
                                {0.5f, 0.9f}, // bottom right
                        },
                        {
                                {0.4f, 1.0f}, // top left
                                {0.5f, 1.0f}, // top right
                                {0.4f, 0.9f}, // bottom left
                                {0.5f, 0.9f}, // bottom right
                        },
                        {
                                {0.3f, 1.0f}, // top left
                                {0.4f, 1.0f}, // top right
                                {0.3f, 0.9f}, // bottom left
                                {0.4f, 0.9f}, // bottom right
                        },
                        {
                                {0.4f, 1.0f}, // top left
                                {0.5f, 1.0f}, // top right
                                {0.4f, 0.9f}, // bottom left
                                {0.5f, 0.9f}, // bottom right
                        },
                        {
                                {0.4f, 1.0f}, // top left
                                {0.5f, 1.0f}, // top right
                                {0.4f, 0.9f}, // bottom left
                                {0.5f, 0.9f}, // bottom right
                        },
                        {
                                {0.4f, 1.0f}, // top left
                                {0.5f, 1.0f}, // top right
                                {0.4f, 0.9f}, // bottom left
                                {0.5f, 0.9f}, // bottom right
                        }
                },
                // Dirt
                {
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                        {
                                {0.5f, 1.0f}, // top left
                                {0.6f, 1.0f}, // top right
                                {0.5f, 0.9f}, // bottom left
                                {0.6f, 0.9f}, // bottom right
                        },
                }
        };


#endif
