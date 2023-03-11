#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace flat
{
    struct RGBAColor
    {
        float r,g,b,a;
        RGBAColor()
            : r(0.0f),g(0.0f),b(0.0f),a(0.0f)
        {}
        ~RGBAColor() = default;
    };

    struct Pixel
    {
        float x,y,z;
        RGBAColor color;
        Pixel()
            : x(0.0f),y(0.0f),z(0.0f)
        {}
        ~Pixel() = default;
    };

    struct Rectangle
    {
        float x,y,z,w,h,rotateX,rotateY,rotateZ;
        std::array<float,2> texCoord1,texCoord2,texCoord3,texCoord4;
        std::array<RGBAColor,4> colors;
        Rectangle()
            : x(0.0f),y(0.0f),z(0.0f),w(0.0f),h(0.0f),rotateX(0.0f),rotateY(0.0f),rotateZ(0.0f),
            texCoord1({0.0f,0.0f}),
            texCoord2({0.0f,0.0f}),
            texCoord3({0.0f,0.0f}),
            texCoord4({0.0f,0.0f})
        {}
        ~Rectangle() = default;
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
        ~Triangle() = default;
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
        virtual ~Renderer() {}
        virtual void initRenderer() = 0;
        virtual void bindTexture(uint32_t texPortId,Texture& texture) = 0;
        virtual void cleanScreen(const RGBAColor& color) = 0;
        virtual void drawPixel(const Pixel& pixel) = 0;
        virtual void drawRectangle(const Rectangle& rectangle) = 0;
        virtual void drawTriangle(const Triangle& triangle) = 0;
        virtual void makeupTriangle(Triangle* triangle) = 0;
        virtual void makeupRectangle(Rectangle* rectangle) = 0;
    };
}