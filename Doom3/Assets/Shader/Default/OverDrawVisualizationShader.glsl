#VERTEX
#version 460 core

#include ../common/uniforms.txt

layout(location = 0) in vec3 aPos;
layout(location = 0) uniform mat4 model;

void main()
{
	gl_Position =  viewProjection * model * vec4(aPos, 1.0);
}

#FRAGMENT
#version 460 core

layout (location = 0) out vec4 oOverdrawIntensity;

void main()
{
	oOverdrawIntensity = vec4(0.1, 0.0, 0.0, 1.0);
}
