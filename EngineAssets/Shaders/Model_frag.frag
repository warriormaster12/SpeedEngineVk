#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragViewVec;
layout(location = 4) in vec3 fragLightVec;

layout(location = 0) out vec4 outColor;
layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform sampler2D normalTexSampler;

layout(push_constant) uniform PushConstants
{
    bool Unlit;
} pushConst;


void main() {
    vec3 texColor = texture(texSampler, fragTexCoord).xyz;
    if(pushConst.Unlit)
    {
        outColor = vec4(texColor, 1.0);
    }
    else 
    {
        vec3 N = normalize(texture(normalTexSampler, fragTexCoord).xyz);
        vec3 L = normalize(fragLightVec);
        vec3 V = normalize(fragViewVec);
        vec3 R = reflect(-L, N);

        vec3 ambient = texColor * 0.1;
        vec3 diffuse = max(dot(N, L), 0.0) * texColor;
        vec3 specular = pow(max(dot(R, V), 0.0), 4.0) *vec3(0.35);

        outColor = vec4(ambient + diffuse + specular, 1.0);
    }
    
}


