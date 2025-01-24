//
// Created by winlogon on 20.01.2025.
//

#ifndef VULKAN_LEARN_TRIANGLEVULKAN_H
#define VULKAN_LEARN_TRIANGLEVULKAN_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstring>
#include <algorithm>
#include <fstream>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class TriangleVulkan{
public:
    void run();

private:
    void initVulkan();
    void initWindow();
    void createInstance();
    void checkGlfwExtension(VkInstanceCreateInfo &createInfo);
    void checkVkExtension();
    void createSurface();
    void pickPhysicalDevice();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(const VkPhysicalDevice& device);
    QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);
    void createLogicalDevice();
    SwapChainSupportDetails queueSwapChainSupport(const VkPhysicalDevice& device);
    VkSurfaceFormatKHR chooseSwapChainFormats(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapChainPresent(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void drawFrame();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();

    //---------------------------------------------------------------------
    static std::vector<char> readFile(const std::string& fileName);
    void cleanup();
    void mainLoop();
    //---------------------------------------------------------------------
    void printPhysicalDevices(const std::vector<VkPhysicalDevice>& devices);
    void printVkExtensions(const std::vector<VkExtensionProperties>& extensions);

private:
    const uint32_t                  WIDTH  = 800;
    const uint32_t                  HEIGHT = 600;
    GLFWwindow*                     window;
    VkInstance                      instance;
    VkPhysicalDevice                physicalDevice = VK_NULL_HANDLE; // физическое устройство
    VkDevice                        device; // логическое устройство
    VkQueue                         graphicsQueue; // для графических операций.
    VkQueue                         presentQueue; // для вывода изображения на экран.
    VkSurfaceKHR                    surface; // Это поверхность отображения, на которую будет выводиться изображение.
    VkSwapchainKHR                  swapChain;
    VkExtent2D                      swapChainExtent;
    VkFormat                        swapChainImageFormat;
    std::vector<VkImage>            swapChainImages;
    std::vector<VkImageView>        swapChainImageViews;
    const std::vector<const char*>  deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    VkRenderPass                    renderPass;
    VkPipeline                      graphicsPipeline;
    VkPipelineLayout                pipelineLayout;
    std::vector<VkFramebuffer>      swapChainFramebuffers;
    VkCommandPool                   commandPool;
    std::vector<VkCommandBuffer>    commandBuffers;
    VkSemaphore                     imageAvailableSemaphore;
    VkSemaphore                     renderFinishedSemaphore;
    VkFence inFlightFence;
    VkCommandBuffer commandBuffer;


};

#endif //VULKAN_LEARN_TRIANGLEVULKAN_H
