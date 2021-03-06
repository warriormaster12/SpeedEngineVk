#include "Engine/Components/Textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Renderer/stb_image/stb_image.h"

void Texture2D::BindTexture(VkCommandPool& commandPool)
{
    createTextureImage(commandPool);
    createTextureImageView();
    createTextureSampler();
};


void Texture2D::createTextureImage(VkCommandPool& commandPool)
{
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }
    VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    bufferInfo.size = imageSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    VkBuffer stagingBuffer;
    VmaAllocation stagingAllocation;
    vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &stagingBuffer, &stagingAllocation, nullptr );

    void* data;
    vmaMapMemory(memory_alloc_ref->allocator, stagingAllocation, &data);
        memcpy(data, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(memory_alloc_ref->allocator, stagingAllocation);

    stbi_image_free(pixels);
    VkImageCreateInfo textureInfo{};
    textureInfo.extent.width = texWidth;
    textureInfo.extent.height = texHeight;
    textureInfo.mipLevels = mipLevels;
    textureInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    textureInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    textureInfo.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

    image_m_ref->createImage(textureInfo, textureImage, textureImageAllocation);
    VkImageMemoryBarrier barrierInfo{};
    barrierInfo.image = textureImage;
    barrierInfo.oldLayout =  VK_IMAGE_LAYOUT_UNDEFINED;
    barrierInfo.newLayout =  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrierInfo.subresourceRange.levelCount = mipLevels;
    image_m_ref->transitionImageLayout(barrierInfo, commandPool);
    image_m_ref->copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), commandPool);
    //transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

    vmaDestroyBuffer(memory_alloc_ref->allocator, stagingBuffer, stagingAllocation);

    image_m_ref->generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, mipLevels, commandPool);
}
void Texture2D::createTextureImageView() {
    VkImageViewCreateInfo textureViewInfo{};
    textureViewInfo.image = textureImage;
    textureViewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    textureViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    textureViewInfo.subresourceRange.levelCount = mipLevels;
    textureImageView = image_m_ref->createImageView(textureViewInfo);
}

void Texture2D::createTextureSampler()
{
    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.minLod = 0;
    samplerInfo.maxLod = static_cast<float>(mipLevels);
    samplerInfo.mipLodBias = 0.0f;

    if (vkCreateSampler(image_m_ref->setup_ref->device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

void Texture2D::DestroyTexture()
{
    vkDestroySampler(image_m_ref->setup_ref->device, textureSampler, nullptr);
    vkDestroyImageView(image_m_ref->setup_ref->device, textureImageView, nullptr);
    
    vmaDestroyImage(memory_alloc_ref->allocator, textureImage, textureImageAllocation);
}


void CubeMapTexture::BindTexture(VkCommandPool& commandPool)
{
    createCubeMapTextureImage(commandPool);
    //createCubeMapTextureImageView();
    //createCubeMapTextureSampler();
};

void CubeMapTexture::createCubeMapTextureImage(VkCommandPool& commandPool)
{
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels;
    for(int i = 0; i < TEXTURE_PATHS.size(); i++)
    {
        pixels = stbi_load(TEXTURE_PATHS[i].c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    }
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }
    VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    bufferInfo.size = imageSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    VkBuffer stagingBuffer;
    VmaAllocation stagingAllocation;
    vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &stagingBuffer, &stagingAllocation, nullptr );

    void* data;
    vmaMapMemory(memory_alloc_ref->allocator, stagingAllocation, &data);
        memcpy(data, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(memory_alloc_ref->allocator, stagingAllocation);

    stbi_image_free(pixels);
    VkImageCreateInfo textureInfo{};
    textureInfo.extent.width = texWidth;
    textureInfo.extent.height = texHeight;
    textureInfo.mipLevels = mipLevels;
    textureInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    textureInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    if (!(textureInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT))
    {
        textureInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }
    // Cube faces count as array layers in Vulkan
    textureInfo.arrayLayers = 6;
    // This flag is required for cube map images
    textureInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

    image_m_ref->createImage(textureInfo, textureImage, textureImageAllocation);
    VkImageMemoryBarrier barrierInfo{};
    barrierInfo.image = textureImage;
    barrierInfo.oldLayout =  VK_IMAGE_LAYOUT_UNDEFINED;
    barrierInfo.newLayout =  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrierInfo.subresourceRange.levelCount = mipLevels;
    image_m_ref->transitionImageLayout(barrierInfo, commandPool);
    image_m_ref->copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), commandPool);
    //transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

    vmaDestroyBuffer(memory_alloc_ref->allocator, stagingBuffer, stagingAllocation);

    image_m_ref->generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, mipLevels, commandPool);    
}