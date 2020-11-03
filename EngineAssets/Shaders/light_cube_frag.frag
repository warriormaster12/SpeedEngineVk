#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

layout(location = 0) out vec4 FragColor; 
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
} ubo;
void main()
{
    FragColor = vec4(0.0, 0.8824, 1.0, 1.0); // set alle 4 vector values to 1.0
}
