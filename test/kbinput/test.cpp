#include <gtest/gtest.h>
#include "glfw_imp.hpp"

TEST(WindowTest, SteadyWindowWithTitle)
{
    kbapi::KeyboardSource<glfwkb::KeyboardSource>&& kbsource = glfwkb::KeyboardSource();

    GLFWwindow* win = glfwGetCurrentContext();
    while(true)
    {
        if(kbsource.checkKey(GLFW_KEY_ESCAPE))
            break;

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