#include "Engine/Renderer/Buffers/VkCommandbuffers.h"


namespace VkRenderer
{
    void VkcommandBuffer::createCommandPool(VkSurfaceKHR& surface)
    {
        QueueFamilyIndices queueFamilyIndices = setup_ref->findQueueFamilies(setup_ref->physicalDevice, surface);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(setup_ref->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }    
    }
    void VkcommandBuffer::createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers, VkExtent2D& swapChainExtent, std::vector<VkDescriptorSet>& descriptorSets)
    {
        commandBuffers.resize(swapChainFramebuffers.size());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

        if (vkAllocateCommandBuffers(setup_ref->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderpass_ref->renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
                
                vkCmdPushConstants(commandBuffers[i], lightpipeline_ref->pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(push_const), &push_const);
                vkCmdPushConstants(commandBuffers[i], gpipeline_ref->pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(push_const), &push_const);
                

                
                for(int j=0; j < scene_ref->meshes.size(); j++)
                {
                    
                    if(scene_ref->meshes[j].current_mesh_type == mesh_types::user_mesh)
                    {
                        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, gpipeline_ref->graphicsPipeline);
                        vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, gpipeline_ref->pipelineLayout, 0, 1, &descriptorSets[j], 0, nullptr);
                    }
                    else
                    {
                        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, lightpipeline_ref->graphicsPipeline);
                        vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, lightpipeline_ref->pipelineLayout, 0, 1, &descriptorSets[j], 0, nullptr);
                    
                    }
                    
                    
                    
                    
                    VkBuffer vertexBuffers[] = {scene_ref->meshes[j].vertexBuffer.vertexBuffer};
                    VkDeviceSize offsets[] = {0};
                    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
                    

                    vkCmdBindIndexBuffer(commandBuffers[i], scene_ref->meshes[j].indexBuffer.indexBuffer, 0, VK_INDEX_TYPE_UINT32);
                    
                    
                    
                    
            
                    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(scene_ref->meshes[j].indexBuffer.indices.size()), 1, 0, 0, 0);
    
                }
                

            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
}