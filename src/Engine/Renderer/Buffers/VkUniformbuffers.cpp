#include "Engine/Renderer/Buffers/VkUnfiormbuffers.h"

namespace VkRenderer
{
    void VkUbuffer::createUniformBuffer()
    {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(meshes.size());
        uniformBuffersMemory.resize(meshes.size());

        for (size_t i = 0; i < meshes.size(); i++) {
            buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }

    void VkUbuffer::updateUniformBuffer(uint32_t DescriptorSetIndex, VkExtent2D& swapChainExtent)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        
        UniformBufferObject ubo{};
        glm::mat4 rotM = glm::mat4(1.0f);

        rotM = glm::rotate(rotM, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotM= glm::rotate(rotM, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotM= glm::rotate(rotM, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = rotM;
        ubo.model = glm::translate(ubo.model, meshes[DescriptorSetIndex]->mesh_transform.translate);
        ubo.model = glm::scale(ubo.model, meshes[DescriptorSetIndex]->mesh_transform.scale);	
        
        camera_object.Set_Camera(swapChainExtent.width / (float) swapChainExtent.height);
        ubo.view = camera_object.matrices.view;
        ubo.proj = camera_object.matrices.perspective;

        camera_object.CameraUpdate(deltaTime);

        ubo.lightPosition = glm::vec3(1.0f, 10000.0f, 0.0f);
    

        void* data;
        vkMapMemory(setup_ref->device, uniformBuffersMemory[DescriptorSetIndex], 0, sizeof(ubo), 0, &data);
            memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(setup_ref->device, uniformBuffersMemory[DescriptorSetIndex]);
    }

    void VkUbuffer::createDescriptorPool()
    {
        std::array<VkDescriptorPoolSize, 2> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(meshes.size());
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(meshes.size());

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(meshes.size());

        if (vkCreateDescriptorPool(setup_ref->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }   
    }
    void VkUbuffer::createDescriptorSets(VkImageView& textureImageView, VkSampler& textureSampler)
    {
        descriptorSets.resize(meshes.size());
        for (size_t i = 0; i < meshes.size(); i++) {
            std::vector<VkDescriptorSetLayout> layouts(meshes.size(), descriptorSetLayout);
            VkDescriptorSetAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = descriptorPool;
            allocInfo.descriptorSetCount = static_cast<uint32_t>(1);
            allocInfo.pSetLayouts = layouts.data();

            
            if (vkAllocateDescriptorSets(setup_ref->device, &allocInfo, &descriptorSets[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate descriptor sets!");
            }

        
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textureImageView;
            imageInfo.sampler = textureSampler;

            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};
           
            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = descriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;
            

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = descriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(setup_ref->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
    void VkUbuffer::createDescriptorSetLayout()
    {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
        samplerLayoutBinding.binding = 1;
        samplerLayoutBinding.descriptorCount = 1;
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        layoutInfo.pBindings = bindings.data();

        if (vkCreateDescriptorSetLayout(setup_ref->device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }
}