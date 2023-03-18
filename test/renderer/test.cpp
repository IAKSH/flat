#include "glcore_imp.hpp"
#include <gtest/gtest.h>

TEST(RendererTest, DrawTTF)
{
    renapi::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    ren.initialize();

    GLFWwindow* win = glfwGetCurrentContext();
    // auto texture = ren.genTexture("../../../demo/images/bird0_0.png");
    auto font = ren.genFont("../../../demo/fonts/unifont-15.0.01.ttf");

    /*
    FT_Face face;
    FT_Library ft;

    if(FT_Init_FreeType(&ft)) std::cout << "error: could not init FreeType Library" << std::endl;

    if(FT_New_Face(ft, "../../../demo/fonts/unifont-15.0.01.ttf", 0, &face))
    {
        std::cout << "error: failed to load font" << std::endl;
        abort();
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // 禁用字节对齐限制

    // 加载字符的字形
    if(FT_Load_Char(face, 'A', FT_LOAD_RENDER))
    {
        std::cout << "error: failed to load Glyph" << std::endl;
        abort();
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto tex = ren.genTexture("../../../demo/images/bird0_0.png");
    */

    float rotate = 0.0f;
    while(true)
    {
        if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ptr->addChar(c, texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x);

        ren << renapi::Color(1.0f, 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*font)("wdnmd",0.0f,0.0f,180.0f);

        //ren << renapi::Color(0.5f, sin(rotate), 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D,texture);
        //ren << renapi::Rectangle(0.1f, 0.0f, 0.0f, 0.2f, 0.2f, rotate);

        rotate += 0.01f;

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    //FT_Done_Face(face);
    //FT_Done_FreeType(ft);

    EXPECT_TRUE(true);
}

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
        ren << renapi::Color(0.5f, 1.0f, 1.0f, 0.5f) << renapi::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << *texture << renapi::Rectangle(sin(rotate / 3), cos(rotate / 3), 0.0f, 0.05f, 0.05f, rotate);
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