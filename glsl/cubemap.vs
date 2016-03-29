#version 330 core
layout (location = 0) in vec3 vsPosition;

out vec3 fsTexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * (view * vec4(vsPosition, 1.f));
    gl_Position = pos.xyww;
    fsTexCoords = vsPosition;
}
