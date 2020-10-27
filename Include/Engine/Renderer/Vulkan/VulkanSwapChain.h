#pragma once 

#include "VulkanIncludes.h"
#include "../../Window/Window.h"
#include "VulkanDevices.h"
#include "VulkanImageHandling.h"



namespace Renderer
{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    class VulkanSwapChain
    {
    public:

        VkSurfaceKHR surface;
        void initializeSwapChain(VulkanDevices& vulkanDevices, AppWindow& win);
        void createSurface(AppWindow& win);
        void createSwapChain(AppWindow& win);
        void createImageViews();
        void pickPhysicalDevice();
        void destroySwapChain();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, AppWindow& win);
        bool isDeviceSuitable(VkPhysicalDevice device);

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;

        VulkanImageHandler vulkanImageHandler;
    private: 
        VulkanDevices* p_vulkanDevices; 
        
    };
}