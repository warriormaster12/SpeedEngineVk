#include "Engine/Renderer/VkRenderer.h"

namespace VkRenderer
{
    Renderer::Renderer()
    {
        //SwapChain
        swap_ref.win_ref = win_ref;
        swap_ref.setup_ref = &setup_ref;
        swap_ref.texture_m_ref = &mesh_ref.texture_m_ref;

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &setup_ref;
        gpipeline_ref.Ubuffer_ref = &mesh_ref.Ubuffer_ref;
        gpipeline_ref.Dbuffer_ref = &Dbuffer_ref;

        //UniformBuffer
        mesh_ref.Ubuffer_ref.setup_ref = &setup_ref;
        mesh_ref.Ubuffer_ref.memory_ref = &memory_ref;
        mesh_ref.Ubuffer_ref.buffer_ref = &buffer_ref;

        //BufferCreation
        buffer_ref.setup_ref = &setup_ref;
        buffer_ref.memory_ref = &memory_ref;
        
        //IndexBuffer
        mesh_ref.Ibuffer_ref.setup_ref = &setup_ref;
        mesh_ref.Ibuffer_ref.buffer_ref = &buffer_ref;

        //VertexBuffer
        mesh_ref.Vbuffer_ref.setup_ref = &setup_ref;
        mesh_ref.Vbuffer_ref.buffer_ref = &buffer_ref;

        //CommandBuffer
        Cbuffer_ref.setup_ref = &setup_ref;
        Cbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Cbuffer_ref.mesh_ref = &mesh_ref;

        //FrameBuffer
        Fbuffer_ref.setup_ref = &setup_ref;
        Fbuffer_ref.swap_ref = &swap_ref;
        Fbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Fbuffer_ref.Dbuffer_ref = &Dbuffer_ref;

        //TextureManager
        mesh_ref.texture_m_ref.setup_ref = &setup_ref;
        mesh_ref.texture_m_ref.buffer_ref = &buffer_ref;
        mesh_ref.texture_m_ref.memory_ref = &memory_ref;

        //DepthBuffer
        Dbuffer_ref.setup_ref = &setup_ref;
        Dbuffer_ref.mesh_ref = &mesh_ref;

        //Mesh
        mesh_ref.setup_ref = &setup_ref;
        mesh_ref.swap_ref = &swap_ref;
    }
}