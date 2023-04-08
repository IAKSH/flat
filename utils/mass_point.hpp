#pragma once

namespace ni::utils
{
    class MassPoint
    {
    private:
        float x,y,z;
        float vx,vy,vz;
        float mass;

    protected:
        MassPoint()
            : x{0.0f},y{0.0f},z{0.0f},vx{0.0f},vy{0.0f},vz{0.0f},mass{1.0f}
        {
        }
        ~MassPoint() = default;

    public:
        const float& getPositionX() const { return x; }
        const float& getPositionY() const { return y; }
        const float& getPositionZ() const { return z; }
        const float& getVelocityX() const { return vx; }
        const float& getVelocityY() const { return vy; }
        const float& getVelocityZ() const { return vz; }
        const float& getMass() const { return mass; }
        void setPositionX(const float& x) { this->x = x; }
        void setPositionY(const float& y) { this->y = y; }
        void setPositionZ(const float& z) { this->z = z; }
        void setVelocityX(const float& vx) { this->vx = vx; }
        void setVelocityY(const float& vy) { this->vy = vy; }
        void setVelocityZ(const float& vz) { this->vz = vz; }
        void setMass(const float& mass) { this->mass = mass; }
    };
}