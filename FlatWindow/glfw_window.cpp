#include "glfw_window.hpp"

flat::FWWindow::FWWindow()
{
}

flat::FWWindow::~FWWindow() {}

void flat::FWWindow::initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "error: can't get load glad" << std::endl;
        abort();
    }
}

void flat::FWWindow::initGLFW()
{
    glfwInit();
    glfwInitHint(GLFW_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    initErrorCallback();

    window = glfwCreateWindow(800, 600, "FALT", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "error: can't create glfw window" << std::endl;
        abort();
    }

    //glfwSwapInterval(3);
}

void flat::FWWindow::initViewport()
{
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height){ glViewport(0, 0, width, height); });
}

void flat::FWWindow::initErrorCallback()
{
    glfwSetErrorCallback([](int error, const char* description){
        std::cout << "GLFW Error | errno: " << errno << " description: " << description << std::endl;});
}

void flat::FWWindow::initWindow()
{
    initGLFW();
    bindContext();
    initGLAD();
    initViewport();
}

void flat::FWWindow::destroyWindow()
{
    glfwDestroyWindow(window);
}

void flat::FWWindow::bindContext()
{
    glfwMakeContextCurrent(window);
}

void flat::FWWindow::setWindowHeight(int h)
{
    int buffer;
    glfwGetWindowSize(window,&buffer,nullptr);
    glfwSetWindowSize(window,buffer,h);
}

void flat::FWWindow::setWindowWidth(int w)
{
    int buffer;
    glfwGetWindowSize(window,nullptr,&buffer);
    glfwSetWindowSize(window,w,buffer);
}

void flat::FWWindow::setWindowTitle(std::string_view t)
{
    glfwSetWindowTitle(window,t.data());
}

void flat::FWWindow::setWindowPosition(int x,int y)
{
    glfwSetWindowPos(window,x,y);
}

int const flat::FWWindow::getWindowPositionX()
{
    int buffer;
    glfwGetWindowPos(window,&buffer,nullptr);
    return buffer;
}

int const flat::FWWindow::getWindowPositionY()
{
    int buffer;
    glfwGetWindowPos(window,nullptr,&buffer);
    return buffer;
}

int const flat::FWWindow::getWindowWidth()
{
    int buffer;
    glfwGetWindowSize(window,&buffer,nullptr);
    return buffer;
}

int const flat::FWWindow::getWindowHeight()
{
    int buffer;
    glfwGetWindowSize(window,nullptr,&buffer);
    return buffer;
}

void const flat::FWWindow::updateWindow()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool const flat::FWWindow::checkKeyboardDown(int code)
{
    return glfwGetKey(window,code) == GLFW_PRESS;
}

bool const flat::FWWindow::checkKeyboardUp(int code)
{
    return glfwGetKey(window,code) == GLFW_RELEASE;
}

bool const flat::FWWindow::checkMouseLeft()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
}

bool const flat::FWWindow::checkMouseRight()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
}

bool const flat::FWWindow::checkMouseMiddle()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_MIDDLE);
}

double const flat::FWWindow::getMousePosX()
{
    double buffer;
    glfwGetCursorPos(window,&buffer,nullptr);
    return buffer;
}

double const flat::FWWindow::getMousePosY()
{
    double buffer;
    glfwGetCursorPos(window,nullptr,&buffer);
    return buffer;
}
