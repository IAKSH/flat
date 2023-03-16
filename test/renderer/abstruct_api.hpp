#pragma once

#include <memory>
#include <string_view>

#include "static_type_check.hpp"

namespace renapi
{
    class Rectangle
    {
    private:
        float posX, posY, posZ, width, height, rotateZ;

    public:
        float const getX() { return posX; }
        float const getY() { return posY; }
        float const getZ() { return posZ; }
        float const getWidth() { return width; }
        float const getHeight() { return height; }
        float const getRotateZ() { return rotateZ; }
        void setX(float f) { posX = f; }
        void setY(float f) { posY = f; }
        void setZ(float f) { posZ = f; }
        void setWidth(float f) { width = f; }
        void setHeight(float f) { height = f; }
        void setRotateZ(float f) { rotateZ = f; }
        Rectangle(float x, float y, float z, float w, float h, float rz) : posX(x), posY(y), posZ(z), width(w), height(h), rotateZ(rz) {}
        virtual ~Rectangle(){};
    };

    class Color
    {
    private:
        const float R, G, B, A;

    public:
        float const getRed() { return R; }
        float const getGreen() { return G; }
        float const getBlue() { return B; }
        float const getAlpha() { return A; }
        Color(float red, float green, float blue, float alpha) : R(red), G(green), B(blue), A(alpha) {}
        ~Color() = default;
    };

    class Texture
    {
    public:
        virtual ~Texture() {}
    };

    class TextureSelectBox
    {
    private:
        float upperLeftX, upperLeftY, width, height;

    public:
        TextureSelectBox(float x, float y, float w, float h) : upperLeftX(x), upperLeftY(y), width(w), height(h) {}
        ~TextureSelectBox(){};
        float getUpperLeftPosX() { return upperLeftX; }
        float getUpperLeftPosY() { return upperLeftY; }
        float getWidth() { return width; }
        float getHeight() { return height; }
    };

    template <typename T>
    concept DrawArgs = stool::same_type<T, Rectangle, Color, Texture>();

    template <typename T> struct Renderer
    {
        template <typename U>
        Renderer<T>& operator<<(U&& u)
            requires(DrawArgs<U>)
        {
            if constexpr(std::is_same<U, Rectangle>())
                static_cast<T*>(this)->imp_drawRectangle(u);
            else if constexpr(std::is_same<U, Color>())
                static_cast<T*>(this)->imp_setColor(u);
            else if constexpr(std::is_same<U, Texture>())
                static_cast<T*>(this)->imp_bindTexture(u);

            return *this;
        }

        std::unique_ptr<Texture> genTexture(std::string_view path) { return static_cast<T*>(this)->imp_genTexture(path); }
        void initialize() { static_cast<T*>(this)->imp_initialize(); }
    };
}  // namespace renapi