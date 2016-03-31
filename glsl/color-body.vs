#version 330 core

layout (location = 0) in vec3 vsPosition;
layout (location = 1) in vec3 vsNormal;
layout (location = 2) in vec3 vsColor;

out vec3 fsPosition;
out vec3 fsNormal;
out vec3 fsColor;

uniform mat4 projection;
uniform mat4 model[16];

void main()
{
    vec4 pos = model[gl_InstanceID] * vec4(vsPosition, 1.f);
    gl_Position = projection * pos;
    
    fsPosition = pos.xyz;
    fsNormal = vsNormal;
    fsColor = vsColor;
}
