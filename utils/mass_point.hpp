#pragma once

namespace ni::utils
{
    class Point
    {
    private:
        float x,y,z;
        float vx,vy,vz;

    protected:
        Point()
            : x{0.0f},y{0.0f},z{0.0f},vx{0.0f},vy{0.0f},vz{0.0f}
        {
        }
        ~Point() = default;

    public:
        const float& getPositionX() const { return x; }
        const float& getPositionY() const { return y; }
        const float& getPositionZ() const { return z; }
        const float& getVelocityX() const { return vx; }
        const float& getVelocityY() const { return vy; }
        const float& getVelocityZ() const { return vz; }
        void setPositionX(const float& x) { this->x = x; }
        void setPositionY(const float& y) { this->y = y; }
        void setPositionZ(const float& z) { this->z = z; }
        void setVelocityX(const float& vx) { this->vx = vx; }
        void setVelocityY(const float& vy) { this->vy = vy; }
        void setVelocityZ(const float& vz) { this->vz = vz; }
    };

    class MassPoint : public Point
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