#include "Engine/Renderer/VkRenderer.h"

namespace VkRenderer
{
    Renderer::Renderer()
    {
        //SwapChain
        swap_ref.win_ref = win_ref;
        swap_ref.setup_ref = &setup_ref;
        swap_ref.texture_m_ref = &texture_m_ref;

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &setup_ref;
        gpipeline_ref.Ubuffer_ref = &Ubuffer_ref;
        gpipeline_ref.Dbuffer_ref = &Dbuffer_ref;

        //UniformBuffer
        Ubuffer_ref.setup_ref = &setup_ref;
        Ubuffer_ref.memory_ref = &memory_ref;

        //BufferCreation
        buffer_ref.setup_ref = &setup_ref;
        buffer_ref.memory_ref = &memory_ref;
        
        //IndexBuffer
        Ibuffer_ref.setup_ref = &setup_ref;
        Ibuffer_ref.buffer_ref = &buffer_ref;

        //VertexBuffer
        Vbuffer_ref.setup_ref = &setup_ref;
        Vbuffer_ref.buffer_ref = &buffer_ref;

        //CommandBuffer
        Cbuffer_ref.setup_ref = &setup_ref;
        Cbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Cbuffer_ref.Ibuffer_ref = &Ibuffer_ref;

        //FrameBuffer
        Fbuffer_ref.setup_ref = &setup_ref;
        Fbuffer_ref.swap_ref = &swap_ref;
        Fbuffer_ref.gpipeline_ref = &gpipeline_ref;
        Fbuffer_ref.Dbuffer_ref = &Dbuffer_ref;

        //TextureManager
        texture_m_ref.setup_ref = &setup_ref;
        texture_m_ref.buffer_ref = &buffer_ref;
        texture_m_ref.memory_ref = &memory_ref;

        //DepthBuffer
        Dbuffer_ref.setup_ref = &setup_ref;
        Dbuffer_ref.texture_m_ref = &texture_m_ref;

        //ModelLoader
        model_ref.Ibuffer_ref = &Ibuffer_ref;
        model_ref.Vbuffer_ref = &Vbuffer_ref;
    }
}