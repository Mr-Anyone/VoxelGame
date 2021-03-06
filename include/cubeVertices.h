#ifndef CUBEVERTICES_H
#define CUBEVERTICES_H

#include "texture.h"


//float frontFaceCubeVertices[] = {
//        // Back face(x, y, z), texture(corner(TextureCoordinate), padding), lighting (a) 0.3f
//        0.0f, 0.0f, 1.0f, TextureCoordinate::bottomLeft, 0.0f, 0.3f, // bottom left
//        1.0f, 0.0f, 1.0f, TextureCoordinate::bottomRight, 0.0f, 0.3f, // bottom right
//        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 0.3f, // top left
//        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 0.3f, // top left
//        1.0f, 1.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.3f, // top right
//        1.0f, 0.0f, 1.0f, TextureCoordinate::bottomRight, 0.0f, 0.3f, // bottom right
//};

float backFaceCubeVertices[] = {
        // Back face(x, y, z), texture(corner(TextureCoordinate), padding), lighting (a) 0.3f
        0.0f, 0.0f, 1.0f, TextureCoordinate::bottomLeft, 0.0f, 0.3f, // bottom left
        1.0f, 0.0f, 1.0f, TextureCoordinate::bottomRight, 0.0f, 0.3f, // bottom right
        1.0f, 1.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.3f, // top right
        1.0f, 1.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.3f, // top right
        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 0.3f, // top left
        0.0f, 0.0f, 1.0f, TextureCoordinate::bottomLeft, 0.0f, 0.3f, // bottom left
};

//float backFaceCubeVertices[] = {
//        // Front face (x, y, z), texture(x, y), lighting (a) lighting 0.6f
//        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.6f, // bottom left
//        1.0f, 0.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 0.6f, // bottom right
//        0.0f, 1.0f, 0.0f, TextureCoordinate::topLeft, 1.0f, 0.6f, // top left
//        0.0f, 1.0f, 0.0f, TextureCoordinate::topLeft, 1.0f, 0.6f, // top left
//        1.0f, 0.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 0.6f, // bottom right
//        1.0f, 1.0f, 0.0f, TextureCoordinate::topRight, 1.0f, 0.6f // top right
//};

float frontFaceCubeVertices[] = {
        // Front face (x, y, z), texture(x, y), lighting (a) lighting 0.6f
        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.6f, // bottom left
        1.0f, 1.0f, 0.0f, TextureCoordinate::topRight, 1.0f, 0.6f, // top right
        1.0f, 0.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 0.6f, // bottom right
        1.0f, 1.0f, 0.0f, TextureCoordinate::topRight, 1.0f, 0.6f, // top right
        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.6f, // bottom left
        0.0f, 1.0f, 0.0f, TextureCoordinate::topLeft, 1.0f, 0.6f, // top left
};

float leftFaceCubeVertices[] = {
        // Left face(x, y, z), texture (x, y), lighting (a) 0.2f lighting
        0.0f, 1.0f, 0.0f, TextureCoordinate::topRight, 1.0f, 0.2f, // top right
        0.0f, 0.0f, 1.0f, TextureCoordinate::bottomLeft, 0.0f, 0.2f, // bottom left
        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 0.2f, // top left
        0.0f, 0.0f, 1.0f, TextureCoordinate::bottomLeft, 0.0f, 0.2f, // bottom left
        0.0f, 1.0f, 0.0f, TextureCoordinate::topRight, 1.0f, 0.2f, // top right
        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 0.2f, // bottom right
};

float rightFaceCubeVertices[] = {
        // Right face(x, y, z), texture(x, y), lighting (a) lighting 0.8f
        1.0f, 1.0f, 0.0f, TextureCoordinate::topLeft, 1.0f, 0.8f, // top left
        1.0f, 1.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.8f, // top right
        1.0f, 0.0f, 1.0f, TextureCoordinate::bottomRight, 0.0f, 0.8f, // bottom right
        1.0f, 0.0f, 1.0f, TextureCoordinate::bottomRight, 0.0f, 0.8f, // bottom right
        1.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.8f, // bottom left
        1.0f, 1.0f, 0.0f, TextureCoordinate::topLeft, 1.0f, 0.8f, // top left
};

float bottomFaceCubeVertices[] = {
        // Bottom face(x, y, z), texture(x, y), lighting (a) lighting 0.1
        1.0f, 0.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.1f, // top right
        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.1f, // bottom left
        0.0f, 0.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 0.1f, // top left
        0.0f, 0.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 0.1f, // bottom left
        1.0f, 0.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 0.1f, // top right
        1.0f, 0.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 0.1f, // bottom right
};

float topFaceCubeVertices[] = {
        // Top face(x, y, z), texture(x, y), lighting (a) 1.0f
        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 1.0f, // top left
        1.0f, 1.0f, 1.0f, TextureCoordinate::topRight, 1.0f, 1.0f, // top right
        1.0f, 1.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 1.0f, // bottom right
        1.0f, 1.0f, 0.0f, TextureCoordinate::bottomRight, 0.0f, 1.0f, // bottom right
        0.0f, 1.0f, 0.0f, TextureCoordinate::bottomLeft, 0.0f, 1.0f, // bottom left
        0.0f, 1.0f, 1.0f, TextureCoordinate::topLeft, 1.0f, 1.0f, // top left
};

#endif