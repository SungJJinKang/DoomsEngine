//@begin_vert
#version 460 core


// global uniform buffer for shared common set of uniforms among programs
// see: https://learnopengl.com/#!Advanced-OpenGL/Advanced-GLSL for table of std140 byte offsets

struct DirectionalLight {
	vec3 Direction;
	vec3 Radiance;
};

struct PointLight {
	vec3 Pos;
	vec3 Radiance;
};

layout (std140, binding = 0) uniform Global
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
    DirectionalLight directionalLight[5];
    PointLight pointLight[16];
    int dirLightCount;
    int pointLightCount;
    //
    float camNear;
    float camFar;
    float ambientLightIntensity;
};



layout(location = 0) in vec3 aPos;

layout(set=0, binding = 0) uniform ModelData
{
	mat4 model;
};

void main()
{
	gl_Position =  viewProjection * model * vec4(aPos, 1.0);
}

//@end

//@begin_frag
#version 460 core

layout (location = 0) out vec4 oOverdrawIntensity;

void main()
{
	oOverdrawIntensity = vec4(0.1, 0.0, 0.0, 1.0);
}
//@end