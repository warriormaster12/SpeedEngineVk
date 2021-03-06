#include "Engine/Renderer/Buffers/VkUniformbuffers.h"

namespace VkRenderer
{
    void VkuniformBuffer::Initialize(VkSetup* setup, VkMemoryAllocator* memory_alloc, Scene* scene)
    {
        setup_ref = setup;
        memory_alloc_ref = memory_alloc;
        scene_ref = scene;
        createDescriptorSetLayout();
    }
    void VkuniformBuffer::createUniformBuffer()
    {
        uniformBuffers.resize(scene_ref->meshes.size());
        lightBuffers.resize(scene_ref->meshes.size());
        
        VkBufferCreateInfo LightBufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        LightBufferInfo.size = sizeof(LightBuffer);
        LightBufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

        VkBufferCreateInfo UniformBufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        UniformBufferInfo.size = sizeof(UniformBufferObject);
        UniformBufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    
        
        uboAllocation.resize(scene_ref->meshes.size());
        lightAllocation.resize(scene_ref->meshes.size());


        for (size_t i = 0; i < scene_ref->meshes.size(); i++) {
            vmaCreateBuffer(memory_alloc_ref->allocator, &LightBufferInfo, &allocInfo, &lightBuffers[i], &lightAllocation[i], nullptr);
            vmaCreateBuffer(memory_alloc_ref->allocator, &UniformBufferInfo, &allocInfo, &uniformBuffers[i], &uboAllocation[i], nullptr);
        }
    }

    void VkuniformBuffer::updateUniformBuffer(int DescriptorSetIndex)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        scene_ref->updateScene(deltaTime);
        
        
        
        UniformBufferObject ubo{};
        LightBuffer lightubo{};
        glm::mat4 ModelMatrix(1.0f);
        ubo.model = ModelMatrix;

        ubo.model = glm::translate(ubo.model, scene_ref->meshes[DescriptorSetIndex].mesh_transform.translate);
        ubo.model = glm::rotate(ubo.model, glm::radians(scene_ref->meshes[DescriptorSetIndex].mesh_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(scene_ref->meshes[DescriptorSetIndex].mesh_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(scene_ref->meshes[DescriptorSetIndex].mesh_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = glm::scale(ubo.model, scene_ref->meshes[DescriptorSetIndex].mesh_transform.scale);	

        ubo.camPos = glm::vec4(glm::vec3(scene_ref->camera.camera_transform.translate), 0.0f);

        lightubo.directional_light.direction = glm::vec4(glm::vec3(-0.2f, -1.0f, -0.3f), 0.0f);
        lightubo.directional_light.ambient = glm::vec4(glm::vec3(0.25f),0.0f);
        lightubo.directional_light.diffuse = glm::vec4(glm::vec3(0.4f),0.0f);
        lightubo.directional_light.specular = glm::vec4(glm::vec3(0.5f),0.0f);
        lightubo.directional_light.light_color = glm::vec4(glm::vec3(1.0f, 0.5f, 0.3f),0.0f);

        lightubo.point_lights[0].visible = glm::vec4(bool(true));
        lightubo.point_lights[1].visible = glm::vec4(bool(true));

    
        lightubo.point_lights[0].position = glm::vec4(glm::vec3(4.0f, 1.5f, 2.0f),0.0f);
        scene_ref->meshes[3].mesh_transform.translate = lightubo.point_lights[0].position;
        lightubo.point_lights[0].ambient = glm::vec4(glm::vec3(0.4f),0.0f);
        lightubo.point_lights[0].diffuse = glm::vec4(glm::vec3(0.7f),0.0f);
        lightubo.point_lights[0].specular = glm::vec4(glm::vec3(1.0f),0.0f);
        lightubo.point_lights[0].light_color = glm::vec4(glm::vec3(1.0f, 1.0f, 1.0f),0.0f);
        if(lightubo.point_lights[0].visible == glm::vec4(bool(true)))
        {
            lightubo.point_lights[0].radius = glm::vec4(0.5f);
        }

        lightubo.point_lights[1].position = glm::vec4(glm::vec3(4.0f, 1.5f, -3.0f),0.0f);

        lightubo.point_lights[1].ambient = glm::vec4(glm::vec3(0.4f),0.0f);
        lightubo.point_lights[1].diffuse = glm::vec4(glm::vec3(0.7f),0.0f);
        lightubo.point_lights[1].specular = glm::vec4(glm::vec3(1.0f),0.0f);
        lightubo.point_lights[1].light_color = glm::vec4(glm::vec3(1.0f, 0.55f, 0.22f), 0.0f);
        if(lightubo.point_lights[1].visible == glm::vec4(bool(true)))
        {
            lightubo.point_lights[1].radius = glm::vec4(0.5f);
        }
        lightubo.spot_light.position = glm::vec4(glm::vec3(scene_ref->camera.camera_transform.translate), 0.0f);
        lightubo.spot_light.direction = glm::vec4(scene_ref->camera.cameraFront, 0.0f);
        lightubo.spot_light.ambient = glm::vec4(glm::vec3(0.0f),0.0f);
        lightubo.spot_light.diffuse = glm::vec4(glm::vec3(1.0f),0.0f);
        lightubo.spot_light.specular = glm::vec4(glm::vec3(1.0f),0.0f);
        lightubo.spot_light.visible = glm::vec4(bool(true));
        
        if(lightubo.spot_light.visible == glm::vec4(bool(true)))
        {
            lightubo.spot_light.radius = glm::vec4(4.0f);
        }
        
        
        lightubo.spot_light.cutOff = glm::vec4(glm::cos(glm::radians(12.5f)));
        lightubo.spot_light.outerCutOff = glm::vec4(glm::cos(glm::radians(15.0f)));
        lightubo.spot_light.light_color = glm::vec4(glm::vec3(1.0f),0.0f);
        scene_ref->camera.CameraUpdate(deltaTime);
        
        
        ubo.view = scene_ref->camera.matrices.view;
        ubo.projection = scene_ref->camera.matrices.perspective;
        
        
    

        void* data;
        vmaMapMemory(memory_alloc_ref->allocator, uboAllocation[DescriptorSetIndex], &data);
            memcpy(data, &ubo, sizeof(ubo));
        vmaUnmapMemory(memory_alloc_ref->allocator, uboAllocation[DescriptorSetIndex]);
        vmaMapMemory(memory_alloc_ref->allocator, lightAllocation[DescriptorSetIndex], &data);
            memcpy(data, &lightubo, sizeof(lightubo));
        vmaUnmapMemory(memory_alloc_ref->allocator, lightAllocation[DescriptorSetIndex]);
    }

    void VkuniformBuffer::createDescriptorPool()
    {
        std::vector<VkDescriptorPoolSize> poolSizes = {
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(scene_ref->meshes.size())),
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(scene_ref->meshes.size())),
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(scene_ref->meshes.size())),
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(scene_ref->meshes.size())),
        };
        VkDescriptorPoolCreateInfo descriptorPoolInfo = descriptorPoolCreateInfo(poolSizes, static_cast<uint32_t>(scene_ref->meshes.size()));
        if (vkCreateDescriptorPool(setup_ref->device, &descriptorPoolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }   
    }
    void VkuniformBuffer::createDescriptorSets()
    {
        descriptorSets.resize(scene_ref->meshes.size());
        for (size_t i = 0; i < scene_ref->meshes.size(); i++) {
            std::vector<VkDescriptorSetLayout> layouts(scene_ref->meshes.size(), descriptorSetLayout);
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
            
            VkDescriptorBufferInfo lightbufferInfo{};
            lightbufferInfo.buffer = lightBuffers[i];
            lightbufferInfo.offset = 0;
            lightbufferInfo.range = sizeof(LightBuffer);

            VkDescriptorImageInfo DiffuseImageInfo{};
            DiffuseImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            DiffuseImageInfo.imageView = scene_ref->meshes[i].DiffuseTexture.textureImageView;
            DiffuseImageInfo.sampler = scene_ref->meshes[i].DiffuseTexture.textureSampler;

            VkDescriptorImageInfo NormalImageInfo{};
            NormalImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            NormalImageInfo.imageView = scene_ref->meshes[i].NormalTexture.textureImageView;
            NormalImageInfo.sampler = scene_ref->meshes[i].NormalTexture.textureSampler;
            std::vector<VkWriteDescriptorSet> descriptorWrites = {
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, nullptr, &bufferInfo, 1),
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, &DiffuseImageInfo, nullptr, 1),
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2, &NormalImageInfo, nullptr, 1),
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 3, nullptr, &lightbufferInfo, 1),
            };
           

            vkUpdateDescriptorSets(setup_ref->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
    void VkuniformBuffer::DestroyUniformBuffer()
    {
        for (size_t i = 0; i < scene_ref->meshes.size(); i++) {
            vmaDestroyBuffer(memory_alloc_ref->allocator, lightBuffers[i], lightAllocation[i]);
            vmaDestroyBuffer(memory_alloc_ref->allocator, uniformBuffers[i], uboAllocation[i]);
        }
    }
    void VkuniformBuffer::createDescriptorSetLayout()
    {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1),
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1),
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 2, 1),
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, 3, 1),
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