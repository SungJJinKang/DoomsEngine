//@begin_vert

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec2 UV0;

void main()
{
	gl_Position =  vec4(vec2(aPos), 0.0, 1.0);
	UV0 = aUV0;
}

//@end

//@begin_frag

#version 460 core

layout (location = 0) in vec2 UV0;

layout (location = 0) out vec4 oColor; // 

layout(binding=0) uniform sampler2D ColorTexture;

// global uniform buffer for shared common set of uniforms among programs
// see: https://learnopengl.com/#!Advanced-OpenGL/Advanced-GLSL for table of std140 byte offsets


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
//@end