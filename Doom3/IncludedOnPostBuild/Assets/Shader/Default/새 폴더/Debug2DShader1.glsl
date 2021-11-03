#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 

#include ../../common/uniforms.txt

out vec3 FragPos;

void main()
{
	gl_Position =  vec4(vec2(aPos), 0.0, 1.0);
}

#FRAGMENT

#version 460 core

layout (location = 0) out vec4 oPosition; // 
layout (location = 1) out vec4 oNormal; // 
layout (location = 2) out vec4 oAlbedoSpec; // 

layout(location = 0) uniform vec4 Color; // location != binding , output and uniform 's explicit location isn't associated with each other

in vec3 FragPos;

void main() 
{ 
	oPosition = vec4(FragPos, 1.0);
	oAlbedoSpec = Color; 

}
