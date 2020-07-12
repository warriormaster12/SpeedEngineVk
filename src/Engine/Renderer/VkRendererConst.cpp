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
    }
}