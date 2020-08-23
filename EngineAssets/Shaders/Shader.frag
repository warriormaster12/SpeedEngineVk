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


void main() {
    //outColor = texture(texSampler, fragTexCoord);

    vec3 N = normalize(fragNormal);
    vec3 L = normalize(fragLightVec);
    vec3 V = normalize(fragViewVec);
    vec3 R = reflect(-L, N);

    vec3 ambient = fragColor * 0.1;
    vec3 diffuse = max(dot(N, L), 0.0) * fragColor;
    vec3 specular = pow(max(dot(R, V), 0.0), 16.0) * vec3(1.35);

    outColor = vec4(ambient + diffuse + specular, 1.0) * texture(texSampler, fragTexCoord);

}


