#version 330 core
layout (location = 0) in vec3 vsPosition;

out vec3 fsTexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * (view * vec4(vsPosition, 1.f));
    fsTexCoords = vsPosition;
}