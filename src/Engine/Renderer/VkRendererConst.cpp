#include "Engine/Renderer/VkRenderer.h"

namespace VkRenderer
{
    Renderer::Renderer()
    {
        //SwapChain
        swap_ref.win_ref = &win_ref;
        swap_ref.setup_ref = &setup_ref;

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &setup_ref;
        gpipeline_ref.swap_ref = &swap_ref;
        gpipeline_ref.Ubuffer_ref = &Ubuffer_ref;

        //UniformBuffer
        Ubuffer_ref.setup_ref = &setup_ref;
        Ubuffer_ref.swap_ref = &swap_ref;
        Ubuffer_ref.memory_ref = &memory_ref;

        //BufferCreation
        buffer_ref.setup_ref = &setup_ref;
        buffer_ref.memory_ref = &memory_ref;
        
    }
}