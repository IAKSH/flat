#include "glcore_imp.hpp"

int main()
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();

    auto texture = ren.genTexture("images/bird0_0.png");
    auto font = ren.genFont("fonts/unifont-15.0.01.ttf");

    GLFWwindow* win = glfwGetCurrentContext();
    float rotate = 0.0f;
    while (true)
    {
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ren << renapi::Color(0.5f, sin(rotate), 1.0f, 0.5f) << renapi::TextureOffset(sin(rotate / 10), 0.1f, sin(rotate / 10), sin(rotate / 5)) << *texture
            << renapi::Rectangle(0.1f, 0.0f, 0.0f, 1.0f, 1.0f, rotate);
        ren << renapi::Color(0.5f, 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture << renapi::Rectangle(sin(rotate / 3), cos(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(sin(rotate / 3), 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture
            << renapi::Rectangle(sin(rotate / 5), cos(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)('w')
            << renapi::Rectangle(cos(rotate / 30), sin(rotate / 20), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)('d')
            << renapi::Rectangle(cos(rotate / 25), sin(rotate / 18), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)('n')
            << renapi::Rectangle(cos(rotate / 20), sin(rotate / 16), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)('m')
            << renapi::Rectangle(cos(rotate / 15), sin(rotate / 14), 0.0f, 0.05f, 0.05f, rotate);
        ren << renapi::Color(0.5f, 1.0f, sin(rotate / 3), 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)('d')
            << renapi::Rectangle(cos(rotate / 10), sin(rotate / 12), 0.0f, 0.05f, 0.05f, rotate);

        rotate += 0.1f;

        glfwPollEvents();
        glfwSwapBuffers(win);
    }
}