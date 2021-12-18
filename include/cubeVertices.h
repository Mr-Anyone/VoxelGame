#ifndef CUBEVERTICES_H
#define CUBEVERTICES_H

float backFaceCubeVertices[] = {
        // Back face(x, y, z), texture(x, y), lighting (a)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.3,// Bottom-left
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.3,// bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.3,// top-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.3,// top-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.3,// top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.3,// bottom-left
};

float frontFaceCubeVertices[] = {
        // Front face (x, y, z), texture(x, y), lighting (a)
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.6,// bottom-left
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.6,// top-right
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.6,// bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.6,// top-right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.6,// bottom-left
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.6,// top-left
};

float leftFaceCubeVertices[] = {
        // Left face(x, y, z), texture (x, y), lighting (a)
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.2,// top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.2,// bottom-left
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.2,// top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.2,// bottom-left
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.2,// top-right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.2,// bottom-right
};
float rightFaceCubeVertices[] = {
        // Right face(x, y, z), texture(x, y), lighting (a)
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.8,// top-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.8,// top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.8,// bottom-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.8,// bottom-right
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.8,// bottom-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.8,// top-left
};
float bottomFaceCubeVertices[] = {
        // Bottom face(x, y, z), texture(x, y), lighting (a)
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.1,// top-right
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.1,// bottom-left
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.1,// top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.1,// bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.1,// top-right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.1,// bottom-right
};
float topFaceCubeVertices[] = {
        // Top face(x, y, z), texture(x, y), lighting (a)
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0,// top-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0,// top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0,// bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0,// bottom-right
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0,// bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0// top-left
};
#endif