//@begin_vert

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

layout (location = 0) out vec2 UV0;
layout (location = 1) out vec3 FragPos;
layout (location = 2) out mat3 TBN;
layout (location = 5) out mat3 invertedTBN;
layout (location = 8) out vec4 ClipSpacePos;
layout (location = 9) out vec4 PrevClipSpacePos;


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

layout(set=0, binding = 0) uniform MatrixData
{
    mat4 model;
    mat4 prevModel;
};

float time;

void main()
{
	UV0 = aUV0;
	FragPos = vec3(model * vec4(aPos, 1.0));
        
    vec3 N = normalize(mat3(model) * aNormal);
    vec3 T = normalize(mat3(model) * aTangent);
    T = normalize(T - dot(N, T) * N);
    // vec3 B = cross(N, T);
    vec3 B = normalize(mat3(model) * aBitangent);

    // TBN must form a right handed coord system.
    // Some models have symetric UVs. Check and fix.
    if (dot(cross(N, T), B) < 0.0)
        T = T * -1.0;
    
    TBN = mat3(T, B, N);
    invertedTBN = transpose(TBN);

    ClipSpacePos     = viewProjection * model * vec4(aPos, 1.0);
    PrevClipSpacePos = prevViewProjection * prevModel * vec4(aPos, 1.0);
	
	gl_Position =  projection * view * vec4(FragPos, 1.0);
}

//@end

//@begin_frag
#version 460 core

layout (location = 0) out vec4 FragColor; // viewpos

layout (location = 0) in vec2 UV0;
layout (location = 1) in vec3 FragPos;
layout (location = 2) in mat3 TBN;
layout (location = 5) in mat3 invertedTBN;
layout (location = 8) in vec4 ClipSpacePos;
layout (location = 9) in vec4 PrevClipSpacePos;

layout(set=0, binding = 0) uniform TextureData
{
    sampler2D Texture1;
};

void main() 
{ 
	FragColor = vec4(texture(Texture1, UV0)); 
}

//@end