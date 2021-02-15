#VERTEX

#version 450 core

layout (location = 0) in vec3 aPos; // this should be world space

#include ../common/uniforms.txt

void main()
{
	gl_Position =  projection * view * vec4(aPos, 1.0);
}

#FRAGMENT
#version 450 core

layout (location = 0) out vec4 FragColor; // viewpos

layout(binding=0) uniform vec4 Color;

void main() 
{ 
	FragColor = Color; 
}
