#include "window.hpp"

#include "log.hpp"
#include "keyevent.hpp"
#include "winevent.hpp"
#include "mousevent.hpp"

flat::core::Window::Window(std::string_view name)
    : winName(name)
{
    LOG_TRACE("Creating window \"{}\"", name.data());

    if (!backendsInitialized)
    {
        LOG_TRACE("Window backends uninitialized, initializing");
        initialize();
        backendsInitialized = true;
    }
    else
        initializeWithoutBackends();
}

flat::core::Window::~Window()
{
	release();
}

GLFWwindow* flat::core::Window::getGLFWWindow()
{
	if (!win)
		LOG_CRITICAL("trying to get an null GLFWWindow named {}", winName);
	return win;
}

void flat::core::Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(win);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void flat::core::Window::setPositionX(int x)
{
    int ori;
    glfwGetWindowPos(win, nullptr, &ori);
    glfwSetWindowPos(win, x, ori);
}

void flat::core::Window::setPositionY(int y)
{
    int ori;
    glfwGetWindowPos(win, &ori, nullptr);
    glfwSetWindowPos(win, ori, y);
}

void flat::core::Window::setWidth(int w)
{
    int ori;
    glfwGetWindowSize(win, nullptr, &ori);
    glfwSetWindowSize(win, w, ori);
}

void flat::core::Window::setHeight(int h)
{
    int ori;
    glfwGetWindowSize(win, &ori, nullptr);
    glfwSetWindowSize(win, ori, h);
}

void flat::core::Window::setTitle(std::string_view title)
{
    glfwSetWindowTitle(win, title.data());
}

void flat::core::Window::setEventCallbackFunc(const std::function<void(Event&)>& func)
{
    callback.func = func;
}

int flat::core::Window::getPositionX()
{
    int x;
    glfwGetWindowPos(win, &x, nullptr);
    return x;
}

int flat::core::Window::getPositionY()
{
    int y;
    glfwGetWindowPos(win, nullptr, &y);
    return y;
}

int flat::core::Window::getWidth()
{
    int w;
    glfwGetWindowSize(win, &w, nullptr);
    return w;
}

int flat::core::Window::getHeight()
{
    int h;
    glfwGetWindowSize(win, nullptr, &h);
    return h;
}

void flat::core::Window::initialize()
{
    LOG_TRACE("Initializing GLFW");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description) {
        LOG_CRITICAL("GLFW Error {}: {}", error, description);
        abort();
        });

    LOG_TRACE("GLFW Initialized");
    LOG_TRACE("Initializing GLAD");

    initializeWithoutBackends();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_CRITICAL("Failed to initialize GLAD");
        abort();
    }

    LOG_INFO("OpenGL Info:");
    LOG_INFO("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
    LOG_INFO("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
    LOG_INFO("  Version: {}", (const char*)glGetString(GL_VERSION));

    LOG_TRACE("GLAD Initialized");

    LOG_TRACE("Binding glfw window user pointer");
    glfwSetWindowUserPointer(win, &callback);
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw window resize callback func");
    glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) 
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);

            WindowResize event(width, height);
            if (callback.func)
                callback.func(event);
        });
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw window close callback func");
    glfwSetWindowCloseCallback(win, [](GLFWwindow* window)
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);
            WindowClose event;
            if (callback.func)
                callback.func(event);
        });
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw key callback func");
    glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_REPEAT:
            case GLFW_PRESS:
            {
                KeyPress event(static_cast<KeyCode>(key));
                if (callback.func)
                    callback.func(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyRelease event(static_cast<KeyCode>(key));
                if (callback.func)
                    callback.func(event);
                break;
            }
            }
        });
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw mouse click callback func");
    glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods)
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MousePress event(button);
                if (callback.func)
                    callback.func(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseRelease event(button);
                if (callback.func)
                    callback.func(event);
                break;
            }
            }
        });
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw mouse scroll callback func");
    glfwSetScrollCallback(win, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);

            MouseScroll event((float)yOffset);
            if (callback.func)
                callback.func(event);
        });
    LOG_TRACE("OK");
    LOG_TRACE("Binding glfw mouse move callback func");
    glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xPos, double yPos)
        {
            Callback& callback = *(Callback*)glfwGetWindowUserPointer(window);

            MouseMove event((float)xPos, (float)yPos);
            if (callback.func)
                callback.func(event);
        });
    LOG_TRACE("OK");

    LOG_TRACE("Window backends initialized");
}

void flat::core::Window::initializeWithoutBackends()
{
    win = glfwCreateWindow(800, 600, winName.data(), nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

void flat::core::Window::release()
{
	glfwDestroyWindow(win);
}
