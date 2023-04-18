#include "menu.hpp"

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
    background.loadFromFile("images/strangeSky.png");
    selectIcon.loadFromFile("images/bird0_0.png");

    // OpenGL
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
}

void Flat::MenuLayer::onDetach()
{

}

static int i = 0;
void Flat::MenuLayer::onUpdate()
{
    vao.set(1,ni::utils::Color(sin((i++) / 100) * 255,0,0,64));
}

void Flat::MenuLayer::onRender()
{
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	trans *= glm::scale(glm::mat4(1.0f), glm::vec3(800.0f, 600.0f, 1.0f));
	trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    shader["transform"] = UniformArg(trans);
    shader["camTrans"] = UniformArg(cam.getTranslateMatrix());

    glBindTexture(GL_TEXTURE_2D,background.getTextureID());
    glBindVertexArray(vao.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
}
