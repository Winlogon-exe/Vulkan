//
// Created by winlogon on 26.01.2025.
//

#include "MyWindow.h"

MyWindow::MyWindow()
{

}

MyWindow::~MyWindow()
{
    if (window)
    {
        destroyWindow();
    }
}

void MyWindow::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);
    window = glfwCreateWindow(WIDTH,HEIGHT,"VULKAN", nullptr, nullptr);
}

void MyWindow::destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

//std::pair<uint32_t,const char**> MyWindow::getExtension()
//{
//    uint32_t glfwExtensionCount = 0;
//    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//    return { glfwExtensionCount,glfwExtensions };
//}

void MyWindow::mainLoop(const std::function<void()>& draw)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        draw();
    }
}

GLFWwindow *MyWindow::getWindow() const {
    return window;
}
