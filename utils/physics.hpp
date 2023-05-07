#pragma once

#include <array>

namespace ni::utils
{
    class Point
    {
    private:
        std::array<float,3> xyz;

    public:
        Point() : xyz{0.0f,0.0f,0.0f} {}
        Point(const float& x,const float& y,const float& z) : xyz{x,y,z} {}
        const float& getPositionX() const {return xyz[0];}
        const float& getPositionY() const {return xyz[1];}
        const float& getPositionZ() const {return xyz[2];}
        void setPositionX(const float& val) {xyz[0] = val;}
        void setPositionY(const float& val) {xyz[1] = val;}
        void setPositionZ(const float& val) {xyz[2] = val;}
    };

    class Rotatable : public Point
    {
    private:
        std::array<float,4> orientation;
        std::array<float,3> right;
        std::array<float,3> up;
        void updateVectors();

    public:
        Rotatable();
        ~Rotatable() = default;
        float getYaw() const;
        float getPitch() const;
        float getRoll() const;
        const auto& getOrientation() const {return orientation;}
        const auto& getRight() const {return right;}
        const auto& getUp() const {return up;}
        void setQuat(const std::array<float,4>& arr) {}
        void rotate(float dUp,float dRight,float dRoll);
        void moveWithDirection(float dFront,float dRight,float dHeight);
    };
}