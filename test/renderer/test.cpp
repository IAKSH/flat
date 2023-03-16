#include "glcore_imp.hpp"
#include <gtest/gtest.h>

TEST(RendererTest, DrawRectangleWithColor)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();

    auto texture = ren.genTexture("../../../demo/images/bird0_0.png");

    GLFWwindow* win = glfwGetCurrentContext();
    float rotate = 0.0f;
    while(true)
    {
        if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ren << renapi::Color(0.5f, sin(rotate), 1.0f, 0.5f) << renapi::TextureOffset(sin(rotate / 10), 0.1f, sin(rotate / 10), sin(rotate / 5)) << *texture
            << renapi::Rectangle(0.1f, 0.0f, 0.0f, 1.0f, 1.0f, rotate);
        ren << renapi::Color(0.5f, 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture
            << renapi::Rectangle(sin(rotate / 3), cos(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(sin(rotate / 3), 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture
            << renapi::Rectangle(sin(rotate / 5), cos(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture
            << renapi::Rectangle(cos(rotate / 3), sin(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);

        rotate += 0.1f;

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    EXPECT_TRUE(true);
}

TEST(RendererTest, DrawRectangleWithTransform)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();

    GLFWwindow* win = glfwGetCurrentContext();
    float rotate = 0.0f;
    while(true)
    {
        if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ren << renapi::Rectangle(0.1f, 0.0f, 0.0f, 0.25f, 0.25f, rotate);

        rotate += 0.1f;

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
        if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

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