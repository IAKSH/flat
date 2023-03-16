#pragma once

#include <string_view>

#include "static_type_check.hpp"

namespace renapi
{
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

    template <typename T>
    concept DrawArgs = stool::same_type<T, Rectangle>();

    template <typename T> struct Renderer
    {
        template <typename U> Renderer<T>& operator<<(U&& u) requires(DrawArgs<U>)
        {
            if constexpr(std::is_same<U, Rectangle>())
                static_cast<T*>(this)->imp_drawRectangle(std::move(u));

            return *this;
        }

        bool initialize() {return static_cast<T*>(this)->imp_initialize();}
    };
}  // namespace renapi