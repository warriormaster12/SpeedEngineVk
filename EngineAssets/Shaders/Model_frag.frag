#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

layout(location = 0) in vec3 FragPos;  
layout(location = 1) in vec3 FragColor;
layout(location = 2) in vec2 TexCoords;
layout(location = 3) in vec3 Normal;  

layout(location = 0) out vec4 outColor;
layout(binding = 1) uniform sampler2D diffuseMap;
layout(binding = 2) uniform sampler2D normalMap;

layout(push_constant) uniform PushConstants
{
    bool Unlit;
} pushConst;

struct Light {
    vec4 position;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float radius;
};

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec4 camPos;
    Light light;
} ubo;


void main() {
    vec3 texColor = texture(diffuseMap, TexCoords).rgb;
    if(pushConst.Unlit)
    {
        outColor = vec4(texColor, 1.0);
    }
    else 
    {
        //ambient
        vec3 ambient = vec3(ubo.light.ambient) * texColor;

        //diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(vec3(ubo.light.position) - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = vec3(ubo.light.diffuse) * diff * texColor;

        //specular 
        vec3 viewDir = normalize(vec3(ubo.camPos) - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
        vec3 specular = vec3(ubo.light.specular) * spec * vec3(0.0f,0.0f,0.0f);

        // attenuation
        float distance    = length(vec3(ubo.light.position) - FragPos);
        float attenuation = ubo.light.radius / (pow(distance, 2.0) + 1.0);;    

        
        ambient  *= attenuation;  
        diffuse   *= attenuation;
        specular *= attenuation;   

        vec3 result = vec3(ambient + diffuse + specular);
        outColor = vec4(result, 1.0f);
    }
    
}


