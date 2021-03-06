#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

layout (location = 0) in vec3 aPos;


layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec3 camPos;
} ubo;

void main()
{
	gl_Position = ubo.projection * ubo.view * ubo.model * vec4(aPos, 1.0);
} 
