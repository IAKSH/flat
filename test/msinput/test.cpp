#include <gtest/gtest.h>
#include "glfw_imp.hpp"

TEST(WindowTest, SteadyWindowWithTitle)
{
    msapi::MouseSource<glfwms::MouseSource>&& msSource = glfwms::MouseSource();

    GLFWwindow* win = glfwGetCurrentContext();
    while(true)
    {
        if(msSource.checkMouseMiddle())
            break;

        if(msSource.checkMouseLeft())
            std::cout << "left click at (" << msSource.getMousePositionX() << ',' << msSource.getMousePositionY() << ")\n";

        if(msSource.checkMouseRight())
            std::cout << "right click at (" << msSource.getMousePositionX() << ',' << msSource.getMousePositionY() << ")\n";

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}