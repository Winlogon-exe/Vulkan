#include "TriangleVulkan.h"

int main()
{
    TriangleVulkan triangle;
    try
    {
        triangle.run();
    }
    catch(const std::exception& exp)
    {
        std::cerr << exp.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
