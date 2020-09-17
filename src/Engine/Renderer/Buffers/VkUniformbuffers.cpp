#include "Engine/Renderer/Buffers/VkUnfiormbuffers.h"

namespace VkRenderer
{
    void VkuniformBuffer::createUniformBuffer()
    {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(meshes.size());
        uniformBuffersMemory.resize(meshes.size());

        for (size_t i = 0; i < meshes.size(); i++) {
            buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }

    void VkuniformBuffer::updateUniformBuffer(uint32_t DescriptorSetIndex, VkExtent2D& swapChainExtent)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        
        UniformBufferObject ubo{};
        glm::mat4 ModelMatrix(1.0f);
        ubo.model = ModelMatrix;

        ubo.model = glm::translate(ubo.model, meshes[DescriptorSetIndex]->mesh_transform.translate);
        ubo.model = glm::rotate(ubo.model, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(meshes[DescriptorSetIndex]->mesh_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = glm::scale(ubo.model, meshes[DescriptorSetIndex]->mesh_transform.scale);	
        
        ubo.light.position = glm::vec3(0.0f, 4.0f, 0.0f);
        ubo.camPos = camera_object.camera_transform.translate;

        ubo.light.ambient = glm::vec3(0.2f,0.2f,0.2f);
        ubo.light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        ubo.light.specular = glm::vec3(1.0f,1.0f,1.0f);

        ubo.light.constant = 1.0f;
        ubo.light.linear = 0.09f;
        ubo.light.quadratic = 0.032f;
        
        camera_object.Set_Camera(swapChainExtent.width / (float) swapChainExtent.height);
        ubo.view = camera_object.matrices.view;
        ubo.projection = camera_object.matrices.perspective;

        camera_object.CameraUpdate(deltaTime);
    

        void* data;
        vkMapMemory(setup_ref->device, uniformBuffersMemory[DescriptorSetIndex], 0, sizeof(ubo), 0, &data);
            memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(setup_ref->device, uniformBuffersMemory[DescriptorSetIndex]);
    }

    void VkuniformBuffer::createDescriptorPool()
    {
        std::vector<VkDescriptorPoolSize> poolSizes = {
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(meshes.size())),
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(meshes.size())),
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(meshes.size()))
        };
        VkDescriptorPoolCreateInfo descriptorPoolInfo = descriptorPoolCreateInfo(poolSizes, static_cast<uint32_t>(meshes.size()));
        if (vkCreateDescriptorPool(setup_ref->device, &descriptorPoolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }   
    }
    void VkuniformBuffer::createDescriptorSets()
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

            VkDescriptorImageInfo DiffuseImageInfo{};
            DiffuseImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            DiffuseImageInfo.imageView = meshes[i]->DiffuseTexture.textureImageView;
            DiffuseImageInfo.sampler = meshes[i]->DiffuseTexture.textureSampler;

            VkDescriptorImageInfo NormalImageInfo{};
            NormalImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            NormalImageInfo.imageView = meshes[i]->NormalTexture.textureImageView;
            NormalImageInfo.sampler = meshes[i]->NormalTexture.textureSampler;
            std::vector<VkWriteDescriptorSet> descriptorWrites = {
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, nullptr, &bufferInfo, 1),
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, &DiffuseImageInfo, nullptr, 1),
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2, &NormalImageInfo, nullptr, 1),
            };
           
            

            vkUpdateDescriptorSets(setup_ref->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
    void VkuniformBuffer::createDescriptorSetLayout()
    {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1),
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1),
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 2, 1),
        };

        VkDescriptorSetLayoutCreateInfo descriptorLayout = descriptorSetLayoutCreateInfo(setLayoutBindings);

        if (vkCreateDescriptorSetLayout(setup_ref->device, &descriptorLayout, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    inline VkDescriptorPoolCreateInfo VkuniformBuffer::descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t maxSets)
    {
        VkDescriptorPoolCreateInfo descriptorPoolInfo{};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = maxSets;
        return descriptorPoolInfo;
    }


    inline VkDescriptorPoolSize VkuniformBuffer::descriptorPoolSize(VkDescriptorType type,uint32_t descriptorCount)
    {
        VkDescriptorPoolSize descriptorPoolSize {};
        descriptorPoolSize.type = type;
        descriptorPoolSize.descriptorCount = descriptorCount;
        return descriptorPoolSize;
    }

    inline VkWriteDescriptorSet VkuniformBuffer::writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding, VkDescriptorImageInfo *imageInfo, VkDescriptorBufferInfo *bufferInfo, uint32_t descriptorCount)
    {
        VkWriteDescriptorSet writeDescriptorSet {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = dstSet;
        writeDescriptorSet.descriptorType = type;
        writeDescriptorSet.dstBinding = binding;
        writeDescriptorSet.pImageInfo = imageInfo;
        writeDescriptorSet.pBufferInfo = bufferInfo;
        writeDescriptorSet.descriptorCount = descriptorCount;
        return writeDescriptorSet;
    }

    inline VkDescriptorSetLayoutBinding VkuniformBuffer::descriptorSetLayoutBinding(VkDescriptorType type,VkShaderStageFlags stageFlags,uint32_t binding,uint32_t descriptorCount)
    {
        VkDescriptorSetLayoutBinding setLayoutBinding {};
        setLayoutBinding.descriptorType = type;
        setLayoutBinding.stageFlags = stageFlags;
        setLayoutBinding.binding = binding;
        setLayoutBinding.descriptorCount = descriptorCount;
        return setLayoutBinding;
    }
    inline VkDescriptorSetLayoutCreateInfo VkuniformBuffer::descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& bindings)
    {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pBindings = bindings.data();
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        return descriptorSetLayoutCreateInfo;
    }
}