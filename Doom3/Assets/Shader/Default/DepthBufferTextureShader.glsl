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

#include ../common/uniforms.txt

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * camNear * camFar) / (camFar + camNear - z * (camFar - camNear));	
}

void main() 
{ 
	float depth = LinearizeDepth(vec4(texture(ColorTexture, UV0)).r) / camFar;
	oColor = vec4(vec3(depth), 1.0);
}
