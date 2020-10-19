#pragma once 

#include "VkIncludes.h"
#include "../Window/Window.h"
#include "VkSetup.h"
#include "VkImageManager.h"


namespace VkRenderer
{
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    class VkSwapChain
    {
    public:

        VkSurfaceKHR surface;
        void Initialize(VkSetup* setup, AppWindow* win, VkImageManager* image_m);
        void createSurface();
        void createSwapChain();
        void createImageViews();
        void pickPhysicalDevice();
        void destroySwap();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        bool isDeviceSuitable(VkPhysicalDevice device);

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;

        AppWindow **win_ref;
        VkSetup *setup_ref;
        VkImageManager *image_m_ref;

    };
}