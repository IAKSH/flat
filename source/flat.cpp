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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// camera.draw(each gameobj)

	glfwSwapBuffers(camera.getWindow());
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
	camera.initializePainter();
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

// NMD，不会分解变换矩阵，暂时不写了
// 现在Camera是不会动的
void flat::Camera::draw(GameObject& go)
{
    go.draw();
}

