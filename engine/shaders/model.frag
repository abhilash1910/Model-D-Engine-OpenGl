#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

void main()
{    
 FragColor = vec4(texture(texture_diffuse, TexCoords));
}