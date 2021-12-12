#ifndef CUBEVERTICES_H
#define CUBEVERTICES_H

static float  backFaceCubeVertices[] = {
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f, // bottom-right    
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-right              
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-right
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // top-left
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left                
};

static float frontFaceCubeVertices[] = {
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
    1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // top-right
    1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // bottom-right        
    1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // top-right
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // top-left    
}; 
static float leftFaceCubeVertices[] ={
      // Left face
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-right
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-left
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-left       
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-left
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-right
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-right
};
static float rightFaceCubeVertices [] = {
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-left
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-right      
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-right          
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-right
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-left
};

static float bottomFaceCubeVertices[] = {
      // Bottom face          
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // top-right
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // bottom-left
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, // top-left        
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // bottom-left
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // top-right
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-right
};

static float topFaceCubeVertices [] = {
  // Top face
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // top-left
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // bottom-right                 
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // bottom-right
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f, // bottom-left  
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f  // top-left              
};
#endif