//@begin_vert

#version 460 core

layout(location = 0) in vec3 aPos;  

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

// this code "layout(location = 0) uniform mat4 model" makes error!!
// Please put it in uniform block
layout(binding = 1, std140) uniform ModelData
{
    mat4 model;
};

void main()
{
    gl_Position = viewProjection * vec4(vec3(model * vec4(aPos, 1.0)), 1.0);
}

//@end

//@begin_frag
#version 460 core


void main()
{
    
}

//@end