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
	// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

	// keyboard
	for(int i = GLFW_KEY_SPACE;i < GLFW_KEY_LAST;i++)
	{
		keys[i] = glfwGetKey(camera.getWindow(), i);
	}

	// mouse
	glfwGetCursorPos(camera.getWindow(), &mouseX, &mouseY);
	mouseLeftClick = glfwGetMouseButton(camera.getWindow(),GLFW_MOUSE_BUTTON_LEFT);
	mouseMiddleClick = glfwGetMouseButton(camera.getWindow(),GLFW_MOUSE_BUTTON_MIDDLE);
	mouseRightClick = glfwGetMouseButton(camera.getWindow(),GLFW_MOUSE_BUTTON_RIGHT);
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

void flat::GamePlay::destroyGLFW()
{
	glfwDestroyWindow(camera.getWindow());
	glfwTerminate();
}

const double &flat::GamePlay::getMousePosX()
{
	return mouseX;
}

const double &flat::GamePlay::getMousePosY()
{
	return mouseY;
}

const bool &flat::GamePlay::checkMouseLeftClick()
{
	return mouseLeftClick;
}

const bool &flat::GamePlay::checkMouseMiddleClick()
{
	return mouseMiddleClick;
}

const bool &flat::GamePlay::checkMouseRightClick()
{
	return mouseRightClick;
}

const bool &flat::GamePlay::checkKey(int key)
{
	if(key < GLFW_KEY_SPACE || key > GLFW_KEY_LAST)
	{
		std::cerr << "[ERROR] key out of range (" << key << ')' << std::endl;
		abort();
	}

	return keys[key];
}

flat::Camera::Camera()
{
}

flat::Camera::~Camera()
{
}

void flat::Camera::draw(GameObject &go)
{
	// set vertex shader transform matrix
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, go.getPositionVec());
	transform = glm::rotate(transform, go.getRotate(), glm::vec3(0.0f, 0.0f, 1.0f));
	setTransfrom(transform);

	// set tex offset
	setTexOffset(go.getTexOffset());

	// then draw
	go.draw();
}
