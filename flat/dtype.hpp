#pragma once

#include <cstddef>
#include <array>
#include <exception>
#include <stdexcept>

#include "../utils/logger.hpp"

namespace ni::flat
{
    template <size_t len>
    class Vector
    {
    private:
        std::array<float,len> data;

    public:
        Vector()
            : data{0.0f}
        {
        }

        template <typename... Args>
        Vector(Args... args)
        {
            static_assert(sizeof...(args) <= len, "too many args");
            size_t i = 0;
            ((data[i-1] = args),...);
        }

        float& operator[](size_t index)
        {
            if(index > len)
            {
                ni::utils::otherLogger()->critical("ni::flat::Vector out of range");
                abort();
            }
            return data[index];
        }

        float getLength() {return len;}
    };

    class Color
    {
    private:
        float r,g,b,a;

    public:
        Color() = default;
        Color(float r,float g,float b,float a)
            : r{r},g{g},b{b},a{a}
        {
        }

        const float& getRed() const { return r; }
        const float& getGreen() const { return g; }
        const float& getBlue() const { return b; }
        const float& getAlpha() const { return a; }
        void setRed(const float& val) { r = val; }
        void setGreen(const float& val) { g = val; }
        void setBlue(const float& val) { b = val; }
        void setAlpha(const float& val) { a = val; }
    };

    class Point
    {
    private:
        float x,y,z;

    public:
        Point() : x{0.0f},y{0.0f},z{0.0f} {}
        Point(float x,float y,float z)
            : x{x},y{y},z{z}
        {
        }
        ~Point() = default;

        const float& getX() const { return x; }
        const float& getY() const { return y; }
        const float& getZ() const { return z; }
        void setX(const float& val) { x = val; }
        void setY(const float& val) { y = val; }
        void setZ(const float& val) { z = val; }
    };

    class Scale
    {
    private:
        float scale;

    public:
        Scale() : scale(0.0f) {}
        Scale(float s) : scale(s) {}

        operator float() const { return scale; }

        Scale operator+(const Scale& other) const { return Scale(scale + other.scale); }
        Scale operator-(const Scale& other) const { return Scale(scale - other.scale); }
        Scale operator*(const Scale& other) const { return Scale(scale * other.scale); }
        Scale operator/(const Scale& other) const { return Scale(scale / other.scale); }
    };
}