cmake_minimum_required(VERSION 3.28)
project(Vulkan_Learn)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan glfw glm)
