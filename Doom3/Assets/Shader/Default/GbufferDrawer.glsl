#VERTEX

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 

out vec2 UV0;

#include ../common/uniforms.txt


void main()
{
    UV0 = aUV0;
	gl_Position =  vec4(aPos, 1.0);
}

#FRAGMENT
#version 460 core

layout (location = 0) out vec4 FragColor; // 
  
in vec2 UV0;

#include ../common/uniforms.txt

layout(location = 0) uniform sampler2D gPosition;
layout(location = 1) uniform sampler2D gNormal;
layout(location = 2) uniform sampler2D gAlbedoSpec;

void main()
{             
    
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, UV0).rgb;
    vec3 Normal = texture(gNormal, UV0).rgb;
    vec3 Albedo = texture(gAlbedoSpec, UV0).rgb;
    float Specular = texture(gAlbedoSpec, UV0).a;
    
    // then calculate lighting as usual
    vec3 lighting = Albedo * 0.1; // hard-coded ambient component
    vec3 viewDir = normalize(camPos - FragPos);
    for(int i = 0; i < pointLightCount; ++i)
    {
        // diffuse
        vec3 lightDir = normalize(pointLight[i].Pos - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * pointLight[i].Radiance;
        lighting += diffuse;
    }
    
    FragColor = vec4(lighting, 1.0);
}  