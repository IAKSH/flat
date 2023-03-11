#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace flat
{
    class FWWindow : public Window, public KeyboardInputSource, public MouseInputSource
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

        virtual void initWindow() override;
        virtual void destroyWindow() override;
        virtual void bindContext() override;
        virtual void setWindowTitle(std::string_view t) override;
        virtual void setWindowWidth(int w) override;
        virtual void setWindowHeight(int h) override;
        virtual void setWindowPosition(int x,int y) override;
        virtual int const getWindowPositionX() override;
        virtual int const getWindowPositionY() override;
        virtual int const getWindowWidth() override;
        virtual int const getWindowHeight() override;
        virtual void const updateWindow() override;
        
        virtual bool const checkKeyboardUp(int code) override;
        virtual bool const checkKeyboardDown(int code) override;

        virtual bool const checkMouseLeft() override;
        virtual bool const checkMouseRight() override;
        virtual bool const checkMouseMiddle() override;
        virtual double const getMousePosX() override;
        virtual double const getMousePosY() override;
    };
}