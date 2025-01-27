//
// Created by winlogon on 20.01.2025.
//

#ifndef VULKAN_LEARN_TRIANGLEVULKAN_H
#define VULKAN_LEARN_TRIANGLEVULKAN_H

#define GLFW_INCLUDE_VULKAN
#include "MyWindow.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <memory>
#include <array>
#include <glm/glm.hpp>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex); // количество байт от одной записи до следующей
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription,2> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        // position from vertex shader
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        // color from vertex shader
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

struct SwapChainSupportDetails {
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
    VkSurfaceCapabilitiesKHR        capabilities;
};

class TriangleVulkan{
public:
    void run();

private:
    void initWindow();
    void initVulkan();
    void createInstance();
    void checkGlfwExtension(VkInstanceCreateInfo &createInfo);
    void checkVkExtension();
    void createSurface();
    void pickPhysicalDevice();
    bool isDeviceSuitable(const VkPhysicalDevice& device);
    QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails queueSwapChainSupport(const VkPhysicalDevice& device);
//----------------------------------------------------------------------------------------------------------------------
    void createLogicalDevice();
    void createSwapChain();
    VkSurfaceFormatKHR chooseSwapChainFormats(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapChainPresent(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& capabilities);
//----------------------------------------------------------------------------------------------------------------------
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
//----------------------------------------------------------------------------------------------------------------------
    void createFramebuffers();
//----------------------------------------------------------------------------------------------------------------------
    void createCommandPool();
//----------------------------------------------------------------------------------------------------------------------
    void createVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
//----------------------------------------------------------------------------------------------------------------------
    void createCommandBuffer();
//----------------------------------------------------------------------------------------------------------------------
    void createSyncObjects();
//----------------------------------------------------------------------------------------------------------------------
    static std::vector<char> readFile(const std::string& fileName);
    void cleanup();
    void cleanupSwapChain();
//----------------------------------------------------------------------------------------------------------------------
    void drawFrame();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
//----------------------------------------------------------------------------------------------------------------------
    void printPhysicalDevices(const std::vector<VkPhysicalDevice>& devices);
    void printVkExtensions(const std::vector<VkExtensionProperties>& extensions);


    void generateCircleVertices(float radius, int segmentCount, glm::vec3 color);
    void generateCircleIndices(int segmentCount);
    void createIndexBuffer();

private:
    std::unique_ptr<MyWindow>       glfwWindow;
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
    VkFence                         inFlightFence;
    VkCommandBuffer                 commandBuffer;

    VkBuffer                        vertexBuffer;
    VkDeviceMemory                  vertexBufferMemory;

    VkBuffer                        indexBuffer;
    VkDeviceMemory                  indexBufferMemory;

     std::vector<Vertex> vertices;
     std::vector<uint16_t> indices;
};

#endif //VULKAN_LEARN_TRIANGLEVULKAN_H
