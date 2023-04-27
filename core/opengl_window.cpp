#include "opengl_window.hpp"
#include "loggers.hpp"
#include "event_keyboard.hpp"
#include "event_window.hpp"
#include "event_mouse.hpp"
#include <exception>


ni::core::opengl::Window::Window(std::string_view name)
    : winName(name)
{
    coreLogger->trace("creating window \"{}\"", name.data());

    if (!backendsInitialized)
    {
        coreLogger->trace("Window backends uninitialized, initializing");
        initialize();
        backendsInitialized = true;
    }
    else
        initializeWithoutBackends();
}

ni::core::opengl::Window::~Window()
{
	release();
}

GLFWwindow* ni::core::opengl::Window::getGLFWWindow()
{
	if (!win)
        coreLogger->critical("trying to get an null GLFWWindow named {}", winName);
	return win;
}

void ni::core::opengl::Window::imp_update()
{
    glfwPollEvents();
    glfwSwapBuffers(win);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ni::core::opengl::Window::imp_onEvent(Event& e)
{
    if(eventCallback)
        eventCallback(e);
}

void ni::core::opengl::Window::imp_setPositionX(const int& x)
{
    int ori;
    glfwGetWindowPos(win, nullptr, &ori);
    glfwSetWindowPos(win, x, ori);
}

void ni::core::opengl::Window::imp_setPositionY(const int& y)
{
    int ori;
    glfwGetWindowPos(win, &ori, nullptr);
    glfwSetWindowPos(win, ori, y);
}

void ni::core::opengl::Window::imp_setWidth(const int& w)
{
    int ori;
    glfwGetWindowSize(win, nullptr, &ori);
    glfwSetWindowSize(win, w, ori);
}

void ni::core::opengl::Window::imp_setHeight(const int& h)
{
    int ori;
    glfwGetWindowSize(win, &ori, nullptr);
    glfwSetWindowSize(win, ori, h);
}

void ni::core::opengl::Window::imp_setTitle(std::string_view title)
{
    glfwSetWindowTitle(win, title.data());
}

void ni::core::opengl::Window::imp_setEventCallbackFunc(const std::function<void(Event&)>& func)
{
    eventCallback = func;
}

int ni::core::opengl::Window::imp_getPositionX()
{
    int x;
    glfwGetWindowPos(win, &x, nullptr);
    return x;
}

int ni::core::opengl::Window::imp_getPositionY()
{
    int y;
    glfwGetWindowPos(win, nullptr, &y);
    return y;
}

int ni::core::opengl::Window::imp_getWidth()
{
    int w;
    glfwGetWindowSize(win, &w, nullptr);
    return w;
}

int ni::core::opengl::Window::imp_getHeight()
{
    int h;
    glfwGetWindowSize(win, nullptr, &h);
    return h;
}

std::string_view ni::core::opengl::Window::imp_getName()
{
    return winName;
}

void ni::core::opengl::Window::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description) {
        coreLogger->critical("GLFW Error {}: {}", error, description);
        std::terminate();
        });

    initializeWithoutBackends();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        coreLogger->critical("Failed to initialize GLAD");
        std::terminate();
    }

    coreLogger->info("OpenGL Info:");
    coreLogger->info("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
    coreLogger->info("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
    coreLogger->info("  Version: {}", (const char*)glGetString(GL_VERSION));

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) 
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(win->imp_getName());
            win->imp_onEvent(event);
        });

    glfwSetWindowCloseCallback(win, [](GLFWwindow* window)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event(win->imp_getName());
            win->imp_onEvent(event);
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
                win->imp_onEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleaseEvent event(static_cast<KeyCode>(key));
                win->imp_onEvent(event);
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
                win->imp_onEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseReleaseEvent event(button);
                win->imp_onEvent(event);
                break;
            }
            }
        });

    glfwSetScrollCallback(win, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event(static_cast<float>(xOffset),static_cast<float>(yOffset));
            win->imp_onEvent(event);
        });

    glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xPos, double yPos)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            MouseMoveEvent event((float)xPos, (float)yPos);
            win->imp_onEvent(event);
        });
}

void ni::core::opengl::Window::initializeWithoutBackends()
{
    win = glfwCreateWindow(800, 600, winName.data(), nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

void ni::core::opengl::Window::release()
{
	glfwDestroyWindow(win);
}
