#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable


layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec4 camPos;
} ubo;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec3 inNormal;

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec3 FragColor;
layout (location = 2) out vec2 TexCoords;
layout (location = 3) out vec3 Normal;

void main()
{
    FragPos = vec3(ubo.model * vec4(inPos, 1.0));
    Normal = mat3(transpose(inverse(ubo.model))) * inNormal;  
    TexCoords = inTexCoords;
    FragColor = inColor;
    
    gl_Position = ubo.projection * ubo.view * vec4(FragPos, 1.0);
}



