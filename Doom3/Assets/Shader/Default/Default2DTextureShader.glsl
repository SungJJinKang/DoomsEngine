#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 

out vec3 FragPos;
out vec2 UV0;

void main()
{
	gl_Position =  vec4(vec2(aPos), 0.0, 1.0);
	UV0 = aUV0;
}

#FRAGMENT

#version 460 core

in vec2 UV0;

layout (location = 0) out vec4 oColor; // 

layout(binding = 0) uniform sampler2D ColorTexture;

void main() 
{ 
	oColor = texture(ColorTexture, UV0);
}
