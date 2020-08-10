#include "Engine/Renderer/VkRenderer.h"

namespace VkRenderer
{
    Renderer::Renderer()
    {
        
        //SwapChain
        swap_ref.win_ref = win_ref;
        swap_ref.setup_ref = &setup_ref;
        swap_ref.texture_m_ref = &m.texture_m_ref;

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &setup_ref;
        gpipeline_ref.Ubuffer_ref = &m.Ubuffer_ref;
        gpipeline_ref.Dbuffer_ref = &Dbuffer_ref;

        //UniformBuffer
        m.Ubuffer_ref.setup_ref = &setup_ref;
        m.Ubuffer_ref.memory_ref = &memory_ref;
        m.Ubuffer_ref.buffer_ref = &buffer_ref;

        //BufferCreation
        buffer_ref.setup_ref = &setup_ref;
        buffer_ref.memory_ref = &memory_ref;
        
        //IndexBuffer
        m.Ibuffer_ref.setup_ref = &setup_ref;
        m.Ibuffer_ref.buffer_ref = &buffer_ref;

        //VertexBuffer
        m.Vbuffer_ref.setup_ref = &setup_ref;
        m.Vbuffer_ref.buffer_ref = &buffer_ref;

        //CommandBuffer
        Cbuffer_ref.setup_ref = &setup_ref;
        Cbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Cbuffer_ref.mesh_ref = &m;

        //FrameBuffer
        Fbuffer_ref.setup_ref = &setup_ref;
        Fbuffer_ref.swap_ref = &swap_ref;
        Fbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Fbuffer_ref.Dbuffer_ref = &Dbuffer_ref;

        //TextureManager
        m.texture_m_ref.setup_ref = &setup_ref;
        m.texture_m_ref.buffer_ref = &buffer_ref;
        m.texture_m_ref.memory_ref = &memory_ref;

        //DepthBuffer
        Dbuffer_ref.setup_ref = &setup_ref;
        Dbuffer_ref.mesh_ref = &m;

        //Mesh
        m.setup_ref = &setup_ref;
        m.swap_ref = &swap_ref;
    }
}