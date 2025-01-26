//
// Created by winlogon on 26.01.2025.
//

#ifndef VULKAN_LEARN_MYWINDOW_H
#define VULKAN_LEARN_MYWINDOW_H

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include <functional>

class MyWindow
{
public:
    MyWindow();
    ~MyWindow();

public:
    void init();
    void destroyWindow();
    void mainLoop(const std::function<void()>& draw);
    std::pair<uint32_t,const char**> getExtension();

public:
    GLFWwindow * getWindow() const;

private:
    const uint32_t WIDTH = 900;
    const uint32_t HEIGHT = 600;
    GLFWwindow *window;
};

#endif // VULKAN_LEARN_MYWINDOW_H

