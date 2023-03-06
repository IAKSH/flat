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
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform,go.getPositionVec());
	transform = glm::rotate(transform,go.getRotate(),glm::vec3(0.0f, 0.0f, 1.0f));
	setTransfrom(transform);

	// then draw
    go.draw();
}

