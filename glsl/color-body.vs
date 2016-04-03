#version 330 core

#define DYNE_MAX_GBALLS 5

layout (location = 0) in vec3 vsPosition;
layout (location = 1) in vec3 vsNormal;

out vec3 fsPosition;
out vec3 fsNormal;
out vec3 fsColor;

uniform mat4 projection;
uniform vec3 color[DYNE_MAX_GBALLS];
uniform mat4 model[DYNE_MAX_GBALLS];

void main()
{
    vec4 pos = model[gl_InstanceID] * vec4(vsPosition, 1.f);
    gl_Position = projection * pos;
    
    fsPosition = pos.xyz;
    fsNormal = vsNormal;
    fsColor = color[gl_InstanceID];
}
