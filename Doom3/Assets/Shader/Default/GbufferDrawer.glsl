//@begin_vert

#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aUV0; 

layout (location = 0) out vec2 UV0;


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


void main()
{
    UV0 = aUV0;
	gl_Position =  vec4(aPos, 1.0);
}

//@end

//@begin_frag
#version 460 core

layout (location = 0) out vec4 FragColor; // 
  
layout (location = 0) in vec2 UV0;

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


const float linear = 0.09;
const float quadratic = 0.032;

layout(binding=0) sampler2D gPosition;
layout(binding=1) sampler2D gNormal;
layout(binding=2) sampler2D gAlbedoSpec;

void main()
{             
    
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, UV0).rgb;
    vec3 Normal = texture(gNormal, UV0).rgb;
    vec3 Albedo = texture(gAlbedoSpec, UV0).rgb;
    float Specular = texture(gAlbedoSpec, UV0).a;
    
    // then calculate lighting as usual
    vec3 lighting = Albedo * ambientLightIntensity; // hard-coded ambient component
    vec3 viewDir = normalize(camPos - FragPos);
    for(int i = 0; i < pointLightCount; ++i)
    {
        // https://learnopengl.com/code_viewer_gh.php?code=src/5.advanced_lighting/8.2.deferred_shading_volumes/8.2.deferred_shading.fs
        // diffuse
        float distance = length(pointLight[i].Pos - FragPos);
        //fif(distance < pointLight[i].Radius)
        //{
            // diffuse
            vec3 lightDir = normalize(pointLight[i].Pos - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * pointLight[i].Radiance;
            // specular
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = pointLight[i].Radiance * spec * Specular;
            // attenuation
            float attenuation = 1.0 / (1.0 + linear * distance + quadratic * distance * distance);
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += diffuse + specular;
        //}
        
        /*
        vec3 lightDir = normalize(pointLight[i].Pos - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * pointLight[i].Radiance;
        lighting += diffuse;
        */
    }
    
    for(int i = 0; i < dirLightCount; ++i)
    {
        vec3 diffuse = max(dot(Normal, -directionalLight[i].Direction), 0.0) * Albedo * directionalLight[i].Radiance;
       
       // specular
        vec3 halfwayDir = normalize(-directionalLight[i].Direction + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0);
        vec3 specular = directionalLight[i].Radiance * spec * Specular;

        lighting += diffuse + specular;
    }
    FragColor = vec4(lighting, 1.0);
}  
//@end