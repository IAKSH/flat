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

    // create VAO
    vao.create(GLBufferType::Static,vertices,indices);
}

void Flat::MenuLayer::onDetach()
{

}

void Flat::MenuLayer::onUpdate()
{

}

void Flat::MenuLayer::onRender()
{

}

void Flat::MenuLayer::onEvent(Event& e)
{

}
