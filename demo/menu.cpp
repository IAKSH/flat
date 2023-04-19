#include "menu.hpp"
#include "../utils/unicode.hpp"
#include "../utils/logger.hpp"
#include <string>
#include <sstream>
#include <string_view>

#include <GLFW/glfw3.h>

Flat::MenuLayer::MenuLayer()
    : Layer("menu")
{
}

void Flat::MenuLayer::onAttach()
{
    // load shader
    shader.loadFromGLSL(vshader,fshader);
    glUniform1i(glGetUniformLocation(shader, "texture0"), 0);

    // load textures
    background.loadFromFile("images/wire.png");
    selectIcon.loadFromFile("images/bird0_0.png");

    // load font
    unifont48.loadFromFile("fonts/unifont-15.0.01.ttf");
    unifont48.resize(48);
    unifont16.loadFromFile("fonts/unifont-15.0.01.ttf");
    unifont16.resize(16);

    // OpenGL
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);

    // move game title
    gameTitle.setPosY(550.0f);
    gameTitle.setPosZ(0.1f);
    info0.setPosY(525.0f);
    info0.setPosZ(0.1f);
    info1.setPosY(500.0f);
    info1.setPosZ(0.1f);
    fpsInfo.set(Point(0.0f,475.0f,0.1f));
    fpsInfo.set(Color(1.0f,0.3f,0.1f,1.0f));

    // move quit button
    quitButton.active();
    quitButton.setPosX(-200.0f);
    quitButton.setPosY(-200.0f);
    quitButton.setPosZ(0.2f);

    // reset v-sync
    //glfwSwapInterval(3);

    // button
    quitButton.onAttach();
}

void Flat::MenuLayer::onDetach()
{

}

void Flat::MenuLayer::onUpdate()
{
    std::u32string buffer = ni::utils::to_u32string(1000.0f / fpsRecoder.getSpanAsMilliSeconds().count());
    fpsInfo.set(buffer);

    vao.set(0,ni::utils::Color(sin(recoder.getSpanAsMilliSeconds().count()  / 5000.0f),0,0,0.25f));
    vao.set(1,ni::utils::Color(sin(recoder.getSpanAsMilliSeconds().count()  / 2000.0f),0,0,0.8f));
    vao.set(2,ni::utils::Color(sin(recoder.getSpanAsMilliSeconds().count()  / 4000.5f),0,0,0.75f));
    vao.set(3,ni::utils::Color(sin(recoder.getSpanAsMilliSeconds().count()  / 10000.0f),0,0,0.4f));

    // update fps recoder
    fpsRecoder.update();
}

void Flat::MenuLayer::onRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	trans *= glm::scale(glm::mat4(1.0f), glm::vec3(400.0f, 300.0f, 1.0f));
	trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    shader["transform"] = UniformArg(trans);
    shader["camTrans"] = UniformArg(cam.getTranslateMatrix());

    glBindTexture(GL_TEXTURE_2D,background.getTextureID());
    glBindVertexArray(vao.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    gameTitle.onRender();
    info0.onRender();
    info1.onRender();
    quitButton.onRender();
    fpsInfo.onRender();
    //texRen.drawText(ni::utils::to_u32string(1000.0f / fpsRecoder.getSpanAsMilliSeconds().count()),Point(0.0f,400.0f,0.9f),
	//			Color(1.0f,1.0f,1.0f,1.0f),ni::utils::Scale(1.0f),&unifont16);
}

void Flat::MenuLayer::onEvent(Event& e)
{
    if(e.getType() == ni::core::EventType::KeyPress)
    {
    	switch (static_cast<ni::core::KeyPressEvent&>(e).getKeyCode())
    	{
    		case ni::core::KeyCode::ESCAPE:
    			ni::core::Application::getInstance()->exit();
    			break;

            default:
                break;
        }
    }

    quitButton.onEvent(e);
}