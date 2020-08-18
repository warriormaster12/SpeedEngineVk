#pragma once 

#include "VkIncludes.h"
#include "../Window/Window.h"
#include "VkSetup.h"
#include "VkTextureManager.h"


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
        void createSurface(GLFWwindow *window);
        void createSwapChain(GLFWwindow *window);
        void createImageViews();
        void pickPhysicalDevice();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow *window);
        bool isDeviceSuitable(VkPhysicalDevice device);

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;

        AppWindow *win_ref;
        VkSetup *setup_ref;
        VkTextureManager *texture_m_ref;

    };
}