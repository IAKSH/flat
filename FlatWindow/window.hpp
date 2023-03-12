#pragma once

#include <array>
#include <string_view>

namespace flat
{
    struct KeyboardInputSource
    {
        virtual ~KeyboardInputSource() {};
        virtual bool const checkKeyboardUp(int code) = 0;
        virtual bool const checkKeyboardDown(int code) = 0;
    };
    struct MouseInputSource
    {
        virtual ~MouseInputSource() {};
        virtual bool const checkMouseLeft() = 0;
        virtual bool const checkMouseRight() = 0;
        virtual bool const checkMouseMiddle()= 0;
        virtual double const getMousePosX() = 0;
        virtual double const getMousePosY() = 0;
    };
     struct RGBAColor
    {
        float r,g,b,a;
        RGBAColor()
            : r(0.0f),g(0.0f),b(0.0f),a(0.0f)
        {}
        virtual ~RGBAColor() {}
    };
    struct Pixel
    {
        float x,y,z;
        RGBAColor color;
        Pixel()
            : x(0.0f),y(0.0f),z(0.0f)
        {}
        virtual ~Pixel() {}
    };
    struct Rectangle
    {
        float x,y,z,w,h,rotateX,rotateY,rotateZ;
        std::array<float,2> texCoord1,texCoord2,texCoord3,texCoord4;
        std::array<RGBAColor,4> colors;
        Rectangle()
            : x(0.0f),y(0.0f),z(0.0f),w(0.5f),h(0.5f),rotateX(0.0f),rotateY(0.0f),rotateZ(0.0f),
            texCoord1({1.0f,1.0f}),
            texCoord2({1.0f,0.0f}),
            texCoord3({0.0f,0.0f}),
            texCoord4({0.0f,1.0f})
        {}
        virtual ~Rectangle() {}
    };
    struct Triangle
    {
        float p1x,p1y,p1z;
        float p2x,p2y,p2z;
        float p3x,p3y,p3z;
        float offsetX,offsetY,offsetZ,rotateX,rotateY,rotateZ;
        std::array<float,2> texCoord1,texCoord2,texCoord3;
        Triangle()
            : p1x(0.0f),p1y(0.0f),p1z(0.0f),p2x(0.0f),p2y(0.0f),p2z(0.0f),p3x(0.0f),p3y(0.0f),p3z(0.0f),
            texCoord1({0.0f,0.0f}),
            texCoord2({0.0f,0.0f}),
            texCoord3({0.0f,0.0f})
        {}
        virtual ~Triangle() {}
    };
    struct Texture
    {
        virtual ~Texture() {}
        virtual void initTexture() = 0;
        virtual void loadTextureFromFile(std::string_view path) = 0;
        virtual uint32_t const getTextureId() = 0;
    };

    struct Renderer
    {
        virtual ~Renderer() {};
        virtual void bindTexture(uint32_t texPortId,Texture& texture) = 0;
        virtual void cleanScreen(const RGBAColor& color) = 0;
        virtual void drawPixel(const Pixel& pixel) = 0;
        virtual void drawRectangle(const Rectangle& rectangle) = 0;
        virtual void drawTriangle(const Triangle& triangle) = 0;
        virtual void makeupTriangle(Triangle* triangle) = 0;
        virtual void makeupRectangle(Rectangle* rectangle) = 0;
    };

    struct Window
    {
        virtual ~Window() {};
        virtual void initWindow() = 0;
        virtual void destroyWindow() = 0;
        virtual void setWindowTitle(std::string_view title) = 0;
        virtual void setWindowWidth(int w) = 0;
        virtual void setWindowHeight(int h) = 0;
        virtual void setWindowPosition(int x,int y) = 0;
        virtual int const getWindowPositionX() = 0;
        virtual int const getWindowPositionY() = 0;
        virtual int const getWindowWidth() = 0;
        virtual int const getWindowHeight() = 0;
        virtual void const updateWindow() = 0;
    };
}