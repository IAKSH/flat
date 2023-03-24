#include "abstruct_api.hpp"
#include "initialized.hpp"

#include <algorithm>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string_view>

namespace glfw
{
    class Window : public winapi::Window<Window>
    {
    private:
        GLFWwindow* window;

        void initGLFW()
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(800, 600, "FLAT", NULL, NULL);
            if(window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                abort();
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
        }

        void initGLAD()
        {
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                abort();
            }
        }

    public:
        Window()
        {
            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glfw") == std::end(init::initialized))
            {
                initGLFW();
                init::initialized.push_back("glfw");
            }
            else
            {
                std::cerr << "warning: window module using glfw window created by other modules" << std::endl;
                window = glfwGetCurrentContext();
            }

            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glad") == std::end(init::initialized))
            {
                initGLAD();
                init::initialized.push_back("glad");
            }
        }

        ~Window()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void imp_updateWindow()
        {
            glfwPollEvents();
            glfwSwapBuffers(window);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void imp_setWindowPosX(int x)
        {
            int oriY;
            glfwGetWindowPos(window, nullptr, &oriY);
            glfwSetWindowPos(window, x, oriY);
        }

        void imp_setWindowPosY(int y)
        {
            int oriX;
            glfwGetWindowPos(window, &oriX, nullptr);
            glfwSetWindowPos(window, oriX, y);
        }

        void imp_setWindowSizeH(int h)
        {
            int oriW;
            glfwGetWindowSize(window,&oriW,nullptr);
            glfwSetWindowSize(window,oriW,h);
        }

        void imp_setWindowSizeW(int w)
        {
            int oriH;
            glfwGetWindowSize(window,nullptr,&oriH);
            glfwSetWindowSize(window,w,oriH);
        }

        void imp_setWindowTitle(std::string_view str)
        {
            glfwSetWindowTitle(window,str.data());
        }

        int imp_getWindowPosX()
        {
            int x;
            glfwGetWindowPos(window,&x, nullptr);
            return x;
        }

        int imp_getWindowPosY()
        {
            int y;
            glfwGetWindowPos(window,nullptr, &y);
            return y;
        }

        int imp_getWindowSizeW()
        {
            int w;
            glfwGetWindowSize(window,&w,nullptr);
            return w;
        }

        int imp_getWindowSizeH()
        {
            int h;
            glfwGetWindowSize(window,nullptr,&h);
            return h;
        }
    };
}  // namespace glfw