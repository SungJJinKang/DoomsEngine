#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 

out vec3 FragPos;

void main()
{
	gl_Position =  vec4(vec2(aPos), 0.0, 1.0);
}

#FRAGMENT

#version 460 core

layout (location = 0) out vec4 oColor; // 

layout(location = 0) uniform vec4 Color;

void main() 
{ 
	oColor = Color;
}
