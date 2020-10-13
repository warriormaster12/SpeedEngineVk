#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable


layout (location = 0) out vec4 FragColor;

layout (location = 2) in vec3 TexCoords;

layout(binding = 1) uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}