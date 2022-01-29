//@begin_vert

#version 460 core

layout (location = 0) in vec3 aPos; 

layout (location = 0) out vec3 FragPos;

void main()
{
	gl_Position =  vec4(vec2(aPos), 0.0, 1.0);
}

//@end

//@begin_frag

#version 460 core

layout (location = 0) out vec4 oColor; // 

layout(set=0, binding = 0) uniform ColorData
{
	vec4 Color;
};

void main() 
{ 
	oColor = Color;
}
//@end