#pragma once

#include <string_view>
#include <utility>

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

    template <typename T>
    concept DrawArgs = stool::same_type<T, Rectangle>();

    template <typename T> struct Renderer
    {
        template <typename U>
        Renderer<T>& operator<<(U&& u)
            requires(DrawArgs<U>)
        {
            if constexpr(std::is_same<U, Rectangle>()) static_cast<T*>(this)->imp_drawRectangle(u);

            return *this;
        }

        void initialize() { static_cast<T*>(this)->imp_initialize(); }
    };
}  // namespace renapi