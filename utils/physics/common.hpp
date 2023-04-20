#pragma once

#include <array>
#include "../template.hpp"

namespace ni::utils
{
    struct AxisCoordinateX : public __Enchased<float>
    {
        AxisCoordinateX(const float& f = 0.0f) : __Enchased(f) {}
    };

    struct AxisCoordinateY : public __Enchased<float>
    {
        AxisCoordinateY(const float& f = 0.0f) : __Enchased(f) {}
    };

    struct AxisCoordinateZ : public __Enchased<float>
    {
        AxisCoordinateZ(const float& f = 0.0f) : __Enchased(f) {}
    };

    template <typename T>
    concept PointReturnType = anySame<T,AxisCoordinateX,AxisCoordinateY,AxisCoordinateZ>();

    class Point
    {
    private:
        std::array<float,3> xyz;

    public:
        Point() : xyz{0.0f,0.0f,0.0f} {}
        Point(const float& x,const float& y,const float& z) : xyz{x,y,z} {}
        ~Point() = default;

        const float& getX() const { return xyz[0]; }
        const float& getY() const { return xyz[1]; }
        const float& getZ() const { return xyz[2]; }
        void setX(const float& x) { xyz[0] = x; }
        void setY(const float& y) { xyz[1] = y; }
        void setZ(const float& z) { xyz[2] = z; }

        template <PointReturnType T>
        const T& get()
        {
            if constexpr (isSame<T,AxisCoordinateX>())
                return AxisCoordinateX(xyz[0]);
            else if constexpr (isSame<T,AxisCoordinateY>())
                return AxisCoordinateY(xyz[1]);
            else if constexpr (isSame<T,AxisCoordinateZ>())
                return AxisCoordinateZ(xyz[2]);
        }

        template <PointReturnType T>
        void set(T&& t)
        {
            if constexpr (isSame<T,AxisCoordinateX>())
                xyz[0] = t;
            else if constexpr (isSame<T,AxisCoordinateY>())
                xyz[1] = t;
            else if constexpr (isSame<T,AxisCoordinateZ>())
                xyz[2] = t;
        }
    };

    struct VelocityX : public __Enchased<float>
    {
        VelocityX(const float& f = 0.0f) : __Enchased(f) {}
    };

    struct VelocityY : public __Enchased<float>
    {
        VelocityY(const float& f = 0.0f) : __Enchased(f) {}
    };

    struct VelocityZ : public __Enchased<float>
    {
        VelocityZ(const float& f = 0.0f) : __Enchased(f) {}
    };

    template <typename T>
    concept VelocityReturnType = anySame<T,VelocityX,VelocityY,VelocityZ>();

    class Velocity
    {
    private:
        std::array<float,3> xyz;

    public:
        Velocity() : xyz{0.0f,0.0f,0.0f} {}
        Velocity(const float& x,const float& y,const float& z) : xyz{x,y,z} {}
        ~Velocity() = default;

        const float& getX() const { return xyz[0]; }
        const float& getY() const { return xyz[1]; }
        const float& getZ() const { return xyz[2]; }
        void setX(const float& x) { xyz[0] = x; }
        void setY(const float& y) { xyz[1] = y; }
        void setZ(const float& z) { xyz[2] = z; }

        template <VelocityReturnType T>
        const T& get() const
        {
            if constexpr (isSame<T,VelocityX>())
                return VelocityX(xyz[0]);
            if constexpr (isSame<T,VelocityY>())
                return VelocityY(xyz[1]);
            if constexpr (isSame<T,VelocityZ>())
                return VelocityZ(xyz[2]);
        }

        template <VelocityReturnType T>
        void set(T&& t)
        {
            if constexpr (isSame<T,VelocityX>())
                xyz[0] = t;
            else if constexpr (isSame<T,VelocityY>())
                xyz[1] = t;
            else if constexpr (isSame<T,VelocityZ>())
                xyz[2] = t;
        }
    };
}