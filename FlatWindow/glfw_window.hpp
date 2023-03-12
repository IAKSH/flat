#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat::gl
{
    class Rectangle : public flat::Rectangle
    {
    private:
        void releaseRectangle();

    public:
        Rectangle();
        ~Rectangle();
        uint32_t vao,vbo,ebo;
    };

    class Triangle : public flat::Triangle
    {
    private:
        void releaseRectangle();

    public:
        Triangle();
        ~Triangle();
        uint32_t vao,vbo,ebo;
    };

    class Shader
    {
    private:
        uint32_t shaderId;
        uint32_t compileVShader(std::string_view source);
        uint32_t compileFShader(std::string_view source);
        void checkVShader(uint32_t vshaderId);
        void checkFShader(uint32_t fshaderId);
        void linkShader(uint32_t vshaderId,uint32_t fshaderId);
        void releaseShader();

    public:
        Shader();
        ~Shader();
        void useShader();
        void compileShader(std::string_view vsource,std::string_view fsource);
        void writeUniformMat4(std::string_view uniform,const glm::mat4& mat);
    };

    class Texture : public flat::Texture
    {
    private:
        uint32_t textureId;
        void releaseTexture();
        void checkTexture();

    public:
        Texture();
        virtual ~Texture() override;
        virtual void initTexture() override;
        virtual void loadTextureFromFile(std::string_view path) override;
        virtual uint32_t const getTextureId() override; 
    };
    class FWWindow : public Window, public KeyboardInputSource, public MouseInputSource, public Renderer
    {
    private:
        Shader universalShader;
        std::string title;
        GLFWwindow* window;
        void initGLFW();
        void initGLAD();
        void initViewport();
        void initErrorCallback();
        void initUniversalShader();
        void bindContext();
    
    public:
        FWWindow();
        virtual ~FWWindow() override;

        virtual void initWindow() override;
        virtual void destroyWindow() override;
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

        virtual void bindTexture(uint32_t texPortId,flat::Texture& texture) override;
        virtual void cleanScreen(const flat::RGBAColor& color) override;
        virtual void drawPixel(const flat::Pixel& pixel) override;
        virtual void drawRectangle(const flat::Rectangle& rectangle) override;
        virtual void drawTriangle(const flat::Triangle& triangle) override;
        virtual void makeupTriangle(flat::Triangle* triangle) override;
        virtual void makeupRectangle(flat::Rectangle* rectangle) override;
    };
}