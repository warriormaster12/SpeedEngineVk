#pragma once 

#include "VkIncludes.h"
#include "../Window/Window.h"
#include "VkSetup.h"

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
        void createSurface(GLFWwindow *window, VkInstance& instance);
        void createSwapChain(VkSetup& setup_ref, AppWindow& win_ref);
        void createImageViews(VkDevice& device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, AppWindow& win_ref);

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;

    private:
        AppWindow glfw_win_ref;

    };
}