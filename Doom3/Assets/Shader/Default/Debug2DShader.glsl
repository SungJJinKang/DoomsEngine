//@begin_vert

#version 460 core

layout (location = 0) in vec3 aPos; 

layout(binding = 0, std140) uniform Global
{
    // trtansformations
    mat4 viewProjection;
    mat4 prevViewProjection;
    mat4 projection;
    mat4 view;
    mat4 invViewz;
    // scene
    vec3 camPos;
    // lighting
    vec3 DirectionalLightDirection[5];
	vec3 DirectionalLightRadiance[5];
    vec3 PointLightPos[16];
	vec3 PointLightRadiance[16];
    int dirLightCount;
    int pointLightCount;
    //
    float camNear;
    float camFar;
    float ambientLightIntensity;
};


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