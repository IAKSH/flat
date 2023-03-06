#include "flat.hpp"

flat::GameObject::GameObject()
{

}

flat::GameObject::~GameObject()
{

}

uint32_t flat::GameObject::getId()
{
	return id;
}

void flat::GameObject::setId(uint32_t n)
{
	id = n;
}

void flat::GameObject::onTick()
{
}

void flat::GameObject::onCreate()
{
}

void flat::GameObject::onDestory()
{
}

void flat::GamePlay::updateFrame()
{
	glfwSwapBuffers(camera.getWindow());
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void flat::GamePlay::customUpdateTick()
{

}

void flat::GamePlay::customUpdateInput()
{
}

void flat::GamePlay::updateTick()
{

}

void flat::GamePlay::updateInput()
{
	
	glfwPollEvents();
	// test
	if (glfwGetKey(camera.getWindow(), GLFW_KEY_ESCAPE))
		keyboardInput = GLFW_KEY_ESCAPE;
}

flat::GamePlay::GamePlay()
{
	
}

flat::GamePlay::~GamePlay()
{

}

void flat::GamePlay::update()
{
	updateInput();
    customUpdateInput();
	updateTick();
    customUpdateTick();
	updateFrame();
}

flat::Camera::Camera()
{

}

flat::Camera::~Camera()
{

}

void flat::Camera::draw(GameObject& go)
{
	// set vertex shader transform matrix
	//setTransfrom(glm::translate(glm::mat4(1.0f),go.getPositionVec()));
	//setUniform("xyoffset",{0.5f,0.5f});

	// then draw
    go.draw();
}

