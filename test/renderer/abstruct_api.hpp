#pragma once

#include <string_view>

#include "static_type_check.hpp"

namespace renapi
{
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

    class Rectangle
    {
    private:
        float x, y, z, w, h, rx, ry, rz;

    public:
        float const getX() { return x; }
        float const getY() { return y; }
        float const getZ() { return z; }
        float const getWidth() { return w; }
        float const getHeight() { return h; }
        float const getRotateX() { return rx; }
        float const getRotateY() { return ry; }
        float const getRotateZ() { return rz; }
        void setX(float f) { x = f; }
        void setY(float f) { y = f; }
        void setZ(float f) { z = f; }
        void setWidth(float f) { w = f; }
        void setHeight(float f) { h = f; }
        void setRotateX(float f) { rx = f; }
        void setRotateY(float f) { ry = f; }
        void setRotateZ(float f) { rz = f; }
        Rectangle(float x, float y, float z, float w, float h, float rx, float ry, float rz) {}
        virtual ~Rectangle(){};
    };

    struct Texture
    {
        virtual ~Texture() {}
    };

    struct Font
    {
        virtual ~Font() {}
        virtual Font& operator()(const Font& font) = 0;
    };

    inline static struct
    {
    } flush;
    
    using Flush = decltype(flush);

    template <typename T>
    concept DrawArgs = stool::same_type<T, Color, Texture, Rectangle, Flush, Font>();

    template <typename T> struct Renderer
    {
        template <typename U> Renderer<T>& operator<<(U&& u) requires(DrawArgs<U>)
        {
            using UType = std::remove_cvref<U>;
            if constexpr(std::is_same<UType, Color>())
                static_cast<T*>(this)->imp_setColor(u);
            else if constexpr(std::is_same<UType, Texture>())
                static_cast<T*>(this)->imp_bindTexture(u);
            else if constexpr(std::is_same<UType, Rectangle>())
                static_cast<T*>(this)->imp_drawRectangle(u);
            else if constexpr(std::is_same<UType, Flush>())
                static_cast<T*>(this)->imp_drawFlush();
            else if constexpr(std::is_same<UType, Font>())
                static_cast<T*>(this)->imp_drawText(u);

            return *this;
        }

        const Texture& genTexture(std::string_view path) { return static_cast<T*>(this)->imp_genTexture(path); }
        const Font& genFont(std::string_view path) { return static_cast<T*>(this)->imp_genFont(path); }
        bool initialize() {return static_cast<T*>(this)->imp_initialize();}
    };
}  // namespace renapi