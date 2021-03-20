#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 

void main()
{
	gl_Position =  vec4(aPos, 1.0);
}

#FRAGMENT

#version 460 core
 
layout (location = 0) out vec4 oColor; // 

void main() 
{
	oColor = vec4(1.0);
}
