#version 330 core 

out vec4 fragColor;
in vec2 textureCor;
in float light;
uniform sampler2D texture0; // this will be the texture atlas

void main() 
{
    fragColor = light * texture(texture0, textureCor);
}