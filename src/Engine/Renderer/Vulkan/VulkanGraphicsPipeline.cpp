#include "Engine/Renderer/Vulkan/VulkanGraphicsPipeline.h"
#include "Engine/Renderer/Vulkan/ObjectBuffers/VulkanVertexBuffers.h"


namespace Renderer
{
    void VulkanGraphicsPipeline::createGraphicsPipeline(VulkanDevices& vulkanDevices, VulkanImages& vulkanImages, VkDescriptorSetLayout descriptorSetLayout)
    {
        std::vector <VkShaderModule> ShaderModules;

        for(int i = 0; i < shaders.size(); i++)
        {
            std::string::size_type remove_fileformat = shaders[i].find('.');
            const std::string processed_shader = shaders[i].substr(0, remove_fileformat);
            std::ifstream current_shader(processed_shader + ".spv");
            
            #ifdef NDEBUG
            if (!current_shader)
            {
                shader_ref.CompileGLSL(shaders[i]);
                std::cout<<shaders[i] + " compiled"<<std::endl;
            }
            #else
            vulkanShaderManager.CompileGLSL(shaders[i]);
            std::cout<<shaders[i] + " compiled"<<std::endl;
            #endif
            auto ShaderCode = vulkanShaderManager.readFile(processed_shader + ".spv");
            VkShaderModule shader_mod = vulkanShaderManager.createShaderModule(ShaderCode, vulkanDevices.device);
            ShaderModules.push_back(shader_mod);
        }

    
        std::vector <VkPipelineShaderStageCreateInfo> shaderStages {loadShader(ShaderModules[0], VK_SHADER_STAGE_VERTEX_BIT), loadShader(ShaderModules[1], VK_SHADER_STAGE_FRAGMENT_BIT)}; 


        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions(vertex_attributes);

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) vulkanImages.vulkanSwapChain.swapChainExtent.width;
        viewport.height = (float) vulkanImages.vulkanSwapChain.swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = vulkanImages.vulkanSwapChain.swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPushConstantRange pushConstant = pushConstantRange(VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(PushConstants), 0);


        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.pNext = nullptr;
        pipelineLayoutInfo.flags = 0;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstant;

        if (vkCreatePipelineLayout(vulkanDevices.device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }


        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = shaderStages.size();
        pipelineInfo.pStages = shaderStages.data();
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = vulkanImages.vulkanRenderPass.renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(vulkanDevices.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }
        for(int i = 0; i < ShaderModules.size(); i++)
        {
            vkDestroyShaderModule(vulkanDevices.device, ShaderModules[i], nullptr);
        }
        
    }
    void VulkanGraphicsPipeline::destroyPipeline(VulkanDevices& vulkanDevices)
    {
        vkDestroyPipeline(vulkanDevices.device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(vulkanDevices.device, pipelineLayout, nullptr);
    }

    inline VkPushConstantRange VulkanGraphicsPipeline::pushConstantRange(VkShaderStageFlags stageFlags,uint32_t size,uint32_t offset)
    {
        VkPushConstantRange pushConstantRange {};
        pushConstantRange.stageFlags = stageFlags;
        pushConstantRange.offset = offset;
        pushConstantRange.size = size;
        return pushConstantRange;
    }
    VkPipelineShaderStageCreateInfo VulkanGraphicsPipeline::loadShader(VkShaderModule module,VkShaderStageFlagBits stage)
    {
        VkPipelineShaderStageCreateInfo ShaderStageInfo{};
        ShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderStageInfo.stage = stage;
        ShaderStageInfo.module = module;
        ShaderStageInfo.pName = "main";

        return ShaderStageInfo;
    }
}