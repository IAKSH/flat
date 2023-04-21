#include "window.hpp"
#include "../utils/logger.hpp"
#include "event_keyboard.hpp"
#include "event_window.hpp"
#include "event_mouse.hpp"
#include <exception>


ni::core::Window::Window(std::string_view name)
    : winName(name)
{
    utils::coreLogger()->trace("creating window \"{}\"", name.data());

    if (!backendsInitialized)
    {
        utils::coreLogger()->trace("Window backends uninitialized, initializing");
        initialize();
        backendsInitialized = true;
    }
    else
        initializeWithoutBackends();
}

ni::core::Window::~Window()
{
	release();
}

GLFWwindow* ni::core::Window::getGLFWWindow()
{
	if (!win)
        utils::coreLogger()->critical("trying to get an null GLFWWindow named {}", winName);
	return win;
}

void ni::core::Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(win);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ni::core::Window::onEvent(Event& e)
{
    if(eventCallback)
        eventCallback(e);
}

void ni::core::Window::setPositionX(int x)
{
    int ori;
    glfwGetWindowPos(win, nullptr, &ori);
    glfwSetWindowPos(win, x, ori);
}

void ni::core::Window::setPositionY(int y)
{
    int ori;
    glfwGetWindowPos(win, &ori, nullptr);
    glfwSetWindowPos(win, ori, y);
}

void ni::core::Window::setWidth(int w)
{
    int ori;
    glfwGetWindowSize(win, nullptr, &ori);
    glfwSetWindowSize(win, w, ori);
}

void ni::core::Window::setHeight(int h)
{
    int ori;
    glfwGetWindowSize(win, &ori, nullptr);
    glfwSetWindowSize(win, ori, h);
}

void ni::core::Window::setTitle(std::string_view title)
{
    glfwSetWindowTitle(win, title.data());
}

void ni::core::Window::setEventCallbackFunc(const std::function<void(Event&)>& func)
{
    eventCallback = func;
}

int ni::core::Window::getPositionX()
{
    int x;
    glfwGetWindowPos(win, &x, nullptr);
    return x;
}

int ni::core::Window::getPositionY()
{
    int y;
    glfwGetWindowPos(win, nullptr, &y);
    return y;
}

int ni::core::Window::getWidth()
{
    int w;
    glfwGetWindowSize(win, &w, nullptr);
    return w;
}

int ni::core::Window::getHeight()
{
    int h;
    glfwGetWindowSize(win, nullptr, &h);
    return h;
}

std::string_view ni::core::Window::getName()
{
    return winName;
}

void ni::core::Window::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description) {
        utils::coreLogger()->critical("GLFW Error {}: {}", error, description);
        std::terminate();
        });

    initializeWithoutBackends();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        utils::coreLogger()->critical("Failed to initialize GLAD");
        std::terminate();
    }

    utils::coreLogger()->info("OpenGL Info:");
    utils::coreLogger()->info("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
    utils::coreLogger()->info("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
    utils::coreLogger()->info("  Version: {}", (const char*)glGetString(GL_VERSION));

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) 
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(win->getName());
            win->onEvent(event);
        });

    glfwSetWindowCloseCallback(win, [](GLFWwindow* window)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event(win->getName());
            win->onEvent(event);
        });

    glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_REPEAT:
            case GLFW_PRESS:
            {
                KeyPressEvent event(static_cast<KeyCode>(key));
                win->onEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleaseEvent event(static_cast<KeyCode>(key));
                win->onEvent(event);
                break;
            }
            }
        });

    glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MousePressEvent event(button);
                win->onEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseReleaseEvent event(button);
                win->onEvent(event);
                break;
            }
            }
        });

    glfwSetScrollCallback(win, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event(static_cast<float>(xOffset),static_cast<float>(yOffset));
            win->onEvent(event);
        });

    glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xPos, double yPos)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            MouseMoveEvent event((float)xPos, (float)yPos);
            win->onEvent(event);
        });
}

void ni::core::Window::initializeWithoutBackends()
{
    win = glfwCreateWindow(800, 600, winName.data(), nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

void ni::core::Window::release()
{
	glfwDestroyWindow(win);
}
