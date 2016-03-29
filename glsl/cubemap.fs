#version 330 core

in vec3 vsTexCoords;

uniform samplerCube skybox;

void main()
{
    color = texture(skybox, vsTexCoords);
}