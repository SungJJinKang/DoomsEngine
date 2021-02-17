#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 

#include ../common/uniforms.txt

void main()
{
	gl_Position =  projection * view * vec4(aPos, 1.0);
}

#FRAGMENT

#version 460 core

layout (location = 0) out vec4 FragColor; // viewpos, 

layout(location = 0) uniform vec4 Color; // location != binding , output and uniform 's explicit location isn't associated with each other

void main() 
{ 
	FragColor = Color; 

}
