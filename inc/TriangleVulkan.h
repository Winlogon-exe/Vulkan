//
// Created by winlogon on 20.01.2025.
//

#ifndef VULKAN_LEARN_TRIANGLEVULKAN_H
#define VULKAN_LEARN_TRIANGLEVULKAN_H

#define GLFW_INCLUDE_VULKAN

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
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

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

    // общее описание того, как вершины расположены в памяти
    // (размер каждой вершины, как они читаются)
    static VkVertexInputBindingDescription getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex); // количество байт от одной записи до следующей
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

//    pos.x  pos.y  color.r  color.g  color.b     |  pos.x  pos.y  color.r  color.g  color.b |  pos.x  pos.y  color.r  color.g  color.b
//    (8 байт)      (12 байт)                     |  (8 байт)      (12 байт)                 |  (8 байт)      (12 байт)
//    ------------------- 20 байт ----------------|----------------- 20 байт ----------------|---------------- 20 байт ----------------

    // это конкретное описание отдельных атрибутов внутри вершины
    // (смещение, формат, связь с location в шейдере)
    static std::array<VkVertexInputAttributeDescription,2> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        // position from vertex shader ( in layout[0])
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; // pos.x,pos.y то есть два float
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        // color from vertex shader ( in layout[1])
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; // color.r  color.g  color.b то есть три float
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

struct SwapChainSupportDetails {
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
    VkSurfaceCapabilitiesKHR        capabilities;
};

class TriangleVulkan {
public:
    void run();

private:

    // 1. Функции для валидации и отладки
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    bool checkValidationLayerSupport();

    // 2. Инициализация окна и Vulkan
    void initWindow();
    void initVulkan();

    // 3. Создание экземпляра Vulkan и проверка расширений
    void createInstance();
    std::vector<const char*> checkGlfwExtension();
    void checkVkExtension();

    // 4. Установка Debug Messenger
    void setupDebugMessenger();

    // 5. Создание поверхности рендеринга (Surface)
    void createSurface();

    // 6. Выбор физического устройства (GPU)
    void pickPhysicalDevice();
    bool isDeviceSuitable(const VkPhysicalDevice& device);
    QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    // 7. Создание логического устройства и очередей
    void createLogicalDevice();

    // 8. Создание Swap Chain
    void createSwapChain();
    void recreateSwapChain();
    SwapChainSupportDetails queueSwapChainSupport(const VkPhysicalDevice& device);
    VkSurfaceFormatKHR chooseSwapChainFormats(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapChainPresent(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createImageViews();

    // 9. Создание Render Pass и графического конвейера (Pipeline)
    void createRenderPass();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);

    // 10. Создание Framebuffer
    void createFramebuffers();

    // 11. Создание Command Pool и буферов команд
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    // 12. Создание буферов (Vertex / Index)
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void createVertexBuffer();
    void createIndexBuffer();
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    // 13. Создание объектов синхронизации (Semaphores, Fences)
    void createSyncObjects();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    // 14. Рендеринг
    void drawFrame();

    // 15. Вспомогательные функции
    static std::vector<char> readFile(const std::string& fileName);
    void printPhysicalDevices(const std::vector<VkPhysicalDevice>& devices);
    void printVkExtensions(const std::vector<VkExtensionProperties>& extensions);
    void generateCircleVertices(float radius, int segmentCount, glm::vec3 color);
    void generateCircleIndices(int segmentCount);
    void mainLoop();

    // 16. Очистка ресурсов
    void cleanup();
    void cleanSyncObjects();
    void cleanupSwapChain();

private:
        // 1. Базовые компоненты (инициализация)
        VkInstance instance;
        GLFWwindow* window;
        const uint32_t WIDTH = 900;
        const uint32_t HEIGHT = 600;
        VkSurfaceKHR surface;
        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        VkDebugUtilsMessengerEXT debugMessenger;

        // 2. Устройство (выбор видеокарты и создание логического устройства)
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        // 3. Swap Chain (цепочка кадров)
        VkSwapchainKHR swapChain;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        // 4. Рендер-процесс (Render Pass, Pipeline, Framebuffers)
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline; // ?
        VkPipelineLayout pipelineLayout; // ?
        std::vector<VkFramebuffer> swapChainFramebuffers;

        // 5. Командные буферы и синхронизация
        VkCommandPool commandPool; // ?
        const int MAX_FRAMES_IN_FLIGHT = 2; // кол-во кадров которые могут готовиться одновременно
        uint32_t currentFrame = 0;
        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<VkSemaphore> imageAvailableSemaphores; // ?
        std::vector<VkSemaphore> renderFinishedSemaphores;// ?
        std::vector<VkFence> inFlightFences; // ??

        // 6. Буферы (Вершины, Индексы)
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;

        bool framebufferResized = false;
};

#endif //VULKAN_LEARN_TRIANGLEVULKAN_H
