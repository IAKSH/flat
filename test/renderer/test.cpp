#include <gtest/gtest.h>
#include "glcore_imp.hpp"

TEST(RendererTest, DrawRectangle)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();
    
    GLFWwindow* win = glfwGetCurrentContext();
    while(true)
    {
        if(glfwGetKey(win,GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ren << renapi::Rectangle(0.5f,0.5f,0.5f,0.5f,0.5f,0.0f,0.0f,0.0f);

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    EXPECT_TRUE(true);
}

TEST(RendererTest, SteadyWindow)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();
    
    GLFWwindow* win = glfwGetCurrentContext();
    while(true)
    {
        if(glfwGetKey(win,GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    EXPECT_TRUE(true);
}

TEST(RendererTest, InitializeBackend)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    EXPECT_TRUE(ren.initialize());
}

int main(int argc, char** argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}