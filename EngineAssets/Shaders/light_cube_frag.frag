#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

layout(location = 0) out vec4 FragColor; 

void main()
{
    FragColor = vec4(1.0); // set alle 4 vector values to 1.0
}
