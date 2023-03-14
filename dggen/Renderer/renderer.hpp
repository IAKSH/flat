#pragma once

#include <array>
#include <string>
#include <string_view>

// abstruct layer of Renderer

namespace dggen
{
    class Rectangle {
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
        Rectangle(float x,float y,float z,float w,float h,float rx,float ry,float rz) {}
        virtual ~Rectangle(){};
    };

    class Color {
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

    struct Texture {
        virtual ~Texture() {}
    };

    struct Font {
        virtual ~Font() {}
        virtual Font& operator() (const Font& font) = 0;
    };

    inline static struct {
    } flush;

    template <typename T>
    concept DrawArgs = same_type<T, Color, Texture, Rectangle, decltype(flush), Font>();

    // abstruct API collection
    template <typename T> struct Renderer {
        template <DrawArgs U> Renderer& operator<<(U&& u)
        {
            if constexpr(std::same_as<U, Color>)
                static_cast<T*>(this)->imp_setColor(u);
            else if constexpr(std::same_as<U, Texture>)
                static_cast<T*>(this)->imp_bindTexture(u);
            else if constexpr(std::same_as<U, Rectangle>)
                static_cast<T*>(this)->imp_drawRectangle(u);
            else if constexpr(std::same_as<U, Font>)
                static_cast<T*>(this)->imp_drawText(u);
            else if constexpr(std::same_as<U, decltype(flush)>)
                static_cast<T*>(this)->imp_flush();

            return *this;
        }

        //void loadShader(std::string_view vshader, std::string_view fshader) { static_cast<T*>(this)->imp_loadShader(vshader, fshader); }
        //void swapShader(std::string_view name) { static_cast<T*>(this)->imp_swapShader(name); }
        //void releaseShader(std::string_view name) { static_cast<T*>(this)->imp_releaseShader(name); }
        const Texture& genTexture(std::string_view path) { return static_cast<T*>(this)->imp_genTexture(path); }
        // void releaseTexture(const Texture& texture) { static_cast<T*>(this)->imp_releaseTexture(texture); }
        const Font& genFont(std::string_view path) { return static_cast<T*>(this)->imp_genFont(path); }
        // void releaseFont(const Font& font) { static_cast<T*>(this)->imp_releaseFont(font); }
    };
}  // namespace dggen