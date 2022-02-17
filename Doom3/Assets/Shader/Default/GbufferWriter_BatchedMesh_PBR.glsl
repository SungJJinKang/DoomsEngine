//@begin_vert

#version 460 core

layout (location = 0) in vec3 aWorldPos;  // All in, out variable should have layout (location = ?) option
layout (location = 1) in vec3 aUV0; 
layout (location = 2) in vec3 aTBN1; 
layout (location = 3) in vec3 aTBN2; 
layout (location = 4) in vec3 aTBN3; 

layout (location = 1) out vec3 UV0; // All in, out variable should have layout (location = ?) option
layout (location = 2) out vec3 FragPos;
layout (location = 3) out mat3 TBN;
layout (location = 6) out mat3 invertedTBN; // 
//If the declared input is an n × m matrix, 
//it will be assigned multiple locations starting with the location specified. 
//The number of locations assigned for each matrix will be the same as for an n-element array of m-component vectors.
layout (location = 9) out vec4 ClipSpacePos;
layout (location = 10) out vec4 PrevClipSpacePos;

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
    FragPos = aWorldPos;
	UV0 = aUV0;
    TBN = mat3(aTBN1, aTBN2, aTBN3);
    invertedTBN = transpose(TBN);

	gl_Position =  viewProjection * vec4(FragPos, 1.0);
}

//@end

//@begin_frag
#version 460 core

layout (location = 1) in vec3 UV0; // All in, out variable should have layout (location = ?) option
layout (location = 2) in vec3 FragPos;
layout (location = 3) in mat3 TBN;
layout (location = 6) in mat3 invertedTBN;
layout (location = 9) in vec4 ClipSpacePos;
layout (location = 10) in vec4 PrevClipSpacePos;


layout (location = 0) out vec4 oPosition; // All in, out variable should have layout (location = ?) option
layout (location = 1) out vec4 oNormal; // 
layout (location = 2) out vec4 oAlbedoSpec; // 

layout(binding=0) uniform sampler2D albedoTexture; // sampler2D should have layout(binding=?) option
layout(binding=1) uniform sampler2D normalTexture;
layout(binding=2) uniform sampler2D metalnessTexture;
layout(binding=3) uniform sampler2D roughnessTexture;
layout(binding=4) uniform samplerCube specularTexture;
layout(binding=5) uniform samplerCube irradianceTexture;
layout(binding=6) uniform sampler2D specularBRDF_LUT;


void main() 
{ 
	oPosition = vec4(FragPos, 1.0); 

    vec3 Normal = normalize(2.0 * texture(normalTexture, UV0.xy).rgb - 1.0);
	Normal = normalize(TBN * Normal);
	oNormal = vec4(Normal, 1.0); 

	oAlbedoSpec = vec4(vec3(texture(albedoTexture, UV0.xy)), 1.0); 
	oAlbedoSpec.a = texture(metalnessTexture, UV0.xy).r; 
}

//@end