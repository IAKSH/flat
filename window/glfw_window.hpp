#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace flat
{
    class FWWindow : public Window
    {
    private:
        std::string title;
        GLFWwindow* window;
        void initGLFW();
        void initGLAD();
        void initViewport();
        void initErrorCallback();
    
    public:
        FWWindow();
        ~FWWindow();
        void initWindow() override;
        void destroyWindow() override;
        void bindContext() override;
        void setWindowTitle(std::string_view t) override;
        void setWindowWidth(int w) override;
        void setWindowHeight(int h) override;
        void setWindowPosition(int x,int y) override;
        int const getWindowPositionX() override;
        int const getWindowPositionY() override;
        int const getWindowWidth() override;
        int const getWindowHeight() override;
        void const updateWindow() override;
    };
}