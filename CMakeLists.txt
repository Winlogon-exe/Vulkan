cmake_minimum_required(VERSION 3.28)
project(Vulkan_Learn)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_executable(Vulkan_Learn src/main.cpp)

target_link_libraries(Vulkan_Learn PRIVATE Vulkan::Vulkan)
