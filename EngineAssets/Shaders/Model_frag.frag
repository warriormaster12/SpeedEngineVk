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
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec3 camPos;
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
        vec3 ambient = ubo.light.ambient * texColor;

        //diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(ubo.light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = ubo.light.diffuse * diff * texColor;

        //specular 
        vec3 viewDir = normalize(ubo.camPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
        vec3 specular = ubo.light.specular * spec * vec3(1.0f,1.0f,1.0f);

        // attenuation
        float distance    = length(ubo.light.position - FragPos);
        float attenuation = 1.0 / (ubo.light.constant + ubo.light.linear * distance + ubo.light.quadratic + (distance * distance));    

        
        ambient  *= attenuation;  
        diffuse   *= attenuation;
        specular *= attenuation;   

        vec3 result = ambient + diffuse + specular;
        outColor = vec4(result, 1.0f);
    }
    
}


