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
    vec4 light_color;

    float radius;
};


layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec4 camPos;
    Light light;
} ubo;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 light_color);

void main() {
    vec3 texColor = texture(diffuseMap, TexCoords).rgb;
    if(pushConst.Unlit)
    {
        outColor = vec4(texColor, 1.0);
    }
    else 
    {

        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(vec3(ubo.camPos) - FragPos);

        vec3 result = CalcPointLight(ubo.light, norm, FragPos, viewDir, vec3(ubo.light.light_color));
        
        outColor = vec4(result, 1.0f);
    }
    
}
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 light_color)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    // attenuation
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = light.radius / (pow(distance, 2.0) + 1.0);;    
    // combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(diffuseMap, TexCoords)) * light_color;
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(diffuseMap, TexCoords)) * light_color;
    vec3 specular = vec3(light.specular) * spec * vec3(0.35f) * light_color;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

