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
        ~Point() = default;

        const float& getPosX() const {return xyz[0];}
        const float& getPosY() const {return xyz[1];}
        const float& getPosZ() const {return xyz[2];}
        void setPosX(const float& val) {xyz[0] = val;}
        void setPosY(const float& val) {xyz[1] = val;}
        void setPosZ(const float& val) {xyz[2] = val;}
    };

    class Velocity
    {
    private:
        std::array<float,3> xyz;

    public:
        Velocity() : xyz{0.0f,0.0f,0.0f} {}
        Velocity(const float& x,const float& y,const float& z) : xyz{x,y,z} {}
        ~Velocity() = default;

        const float& getVelX() const {return xyz[0];}
        const float& getVelY() const {return xyz[1];}
        const float& getVelZ() const {return xyz[2];}
        void setVelX(const float& val) {xyz[0] = val;}
        void setVelY(const float& val) {xyz[1] = val;}
        void setVelZ(const float& val) {xyz[2] = val;}
    };

    class MassPoint : public Point, public Velocity
    {
    private:
        float mass;

    protected:
        MassPoint() :Point(),mass{1.0f} {}
        ~MassPoint() = default;

    public:
        const float& getMass() const { return mass; }
        void setMass(const float& mass) { this->mass = mass; }
    };
}