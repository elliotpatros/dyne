#version 330 core

layout (location = 0) in vec3 vsPosition;
layout (location = 1) in vec3 vsNormal;
layout (location = 2) in vec3 vsColor;

out vec3 fsPos;
out vec3 fsNormal;
out vec3 fsColor;

uniform mat4 model;
uniform mat4 lookAt;
uniform mat4 projection;

void main()
{
    vec4 pos = model * vec4(vsPosition, 1.f);
    gl_Position = projection * (lookAt * pos);
    
    fsPos = pos.xyz;
    fsNormal = vsNormal;
    fsColor = vsColor;
}
