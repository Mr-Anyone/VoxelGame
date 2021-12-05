#include "terrain.h"
#include <iostream>
#include <noise/noise.h>

void makeTerrain()
{
    std::cout << "Hello World" << std::endl; 
    noise::module::Perlin myModule;
    double value = myModule.GetValue (14.50, 20.25, 75.75);
    std::cout << value << std::endl;
}