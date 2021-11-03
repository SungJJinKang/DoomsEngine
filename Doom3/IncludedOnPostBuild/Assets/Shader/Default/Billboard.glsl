#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 UV0;
out vec3 FragPos;
out mat3 TBN;
out mat3 invertedTBN;
out vec4 ClipSpacePos;
out vec4 PrevClipSpacePos;

#include ../common/uniforms.txt

layout(location = 0) uniform mat4 model;

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

    //ClipSpacePos     = viewProjection * model * vec4(aPos, 1.0);
    //PrevClipSpacePos = prevViewProjection * prevModel * vec4(aPos, 1.0);
	
	gl_Position =  projection * view * vec4(FragPos, 1.0);
}

#FRAGMENT
#version 460 core

layout (location = 0) out vec4 oPosition; // 
layout (location = 1) out vec4 oNormal; // 
layout (location = 2) out vec4 oAlbedoSpec; // 

layout(binding=0) uniform sampler2D albedoTexture;
layout(binding=1) uniform sampler2D normalTexture;
layout(binding=2) uniform sampler2D metalnessTexture;
layout(binding=3) uniform sampler2D roughnessTexture;
layout(binding=4) uniform samplerCube specularTexture;
layout(binding=5) uniform samplerCube irradianceTexture;
layout(binding=6) uniform sampler2D specularBRDF_LUT;

in vec2 UV0;
in vec3 FragPos;
in mat3 TBN;
in mat3 invertedTBN;
in vec4 ClipSpacePos;
in vec4 PrevClipSpacePos;

void main() 
{ 
	oPosition = vec4(FragPos, 1.0); 

    vec3 Normal = normalize(2.0 * texture(normalTexture, UV0).rgb - 1.0);
	Normal = normalize(TBN * Normal);
	oNormal = vec4(Normal, 1.0); 

	oAlbedoSpec = vec4(vec3(texture(albedoTexture, UV0)), 1.0); 
	//oAlbedoSpec.a = texture(specularTexture, UV0).r; 
}

