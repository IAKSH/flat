#include <iostream>
#include <gtest/gtest.h>

#include "glfw_imp.hpp"

TEST(WindowTest, WindowResizeW)
{
    winapi::Window<glfw::Window>&& win = glfw::Window();

    for(int i = 200;i < 205;i++)
    {
        win.setWindowSizeW(i);
        EXPECT_EQ(win.getWindowSizeW(), i);
    }
}

TEST(WindowTest, WindowResizeH)
{
    winapi::Window<glfw::Window>&& win = glfw::Window();

    for(int i = 1;i < 10;i++)
    {
        win.setWindowSizeH(i);
        EXPECT_EQ(win.getWindowSizeH(), i);
    }
}

TEST(WindowTest, WindowMoveY)
{
    winapi::Window<glfw::Window>&& win = glfw::Window();

    for(int i = 1;i < 10;i++)
    {
        win.setWindowPosY(i);
        EXPECT_EQ(win.getWindowPosY(), i);
    }
}

TEST(WindowTest, WindowMoveX)
{
    winapi::Window<glfw::Window>&& win = glfw::Window();

    for(int i = 1;i < 10;i++)
    {
        win.setWindowPosX(i);
        EXPECT_EQ(win.getWindowPosX(), i);
    }
}

TEST(WindowTest, SteadyWindowWithTitle)
{
    winapi::Window<glfw::Window>&& win = glfw::Window();

    GLFWwindow* _window = glfwGetCurrentContext();
    win.setWindowTitle("Hello world!");
    while(true)
    {
        if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
        win.updateWindow();
    }

    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}