#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 UV0;
out vec3 FragPos;
out vec3 Normal;

#include ../common/uniforms.txt

layout(location = 0) uniform mat4 model;

void main()
{
	UV0 = aUV0;
	FragPos = vec3(model * vec4(aPos, 1.0));
        
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * aNormal;
	
	gl_Position = projection * view * vec4(FragPos, 1.0);
}

#FRAGMENT
#version 460 core

layout (location = 0) out vec4 oPosition; // 
layout (location = 1) out vec4 oNormal; // 
layout (location = 2) out vec4 oAlbedoSpec; // 

in vec2 UV0;
in vec3 FragPos;
in vec3 Normal;

layout(binding=0) uniform sampler2D diffuseTexture;
layout(binding=1) uniform sampler2D normalTexture;
layout(binding=2) uniform sampler2D metalnessTexture;
layout(binding=3) uniform sampler2D roughnessTexture;
layout(binding=4) uniform samplerCube specularTexture;
layout(binding=5) uniform samplerCube irradianceTexture;
layout(binding=6) uniform sampler2D specularBRDF_LUT;

void main() 
{ 
	oPosition = vec4(FragPos, 1.0); 
	oNormal = vec4(Normal, 1.0); 
	oAlbedoSpec.rgb = vec3(texture(diffuseTexture, UV0)); 
	//oAlbedoSpec.a = texture(specularTexture, UV0).r; 
}

