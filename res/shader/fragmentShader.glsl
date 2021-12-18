#version 330 core 

out vec4 fragColor;
in vec2 textureCor;
in float light;
uniform sampler2D texture1;

void main() 
{
    fragColor = light * texture(texture1, textureCor);
}