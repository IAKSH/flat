#pragma once

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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
        glm::quat orientation;
        glm::vec3 right{1.0f,0.0f,0.0f};
        glm::vec3 up{0.0f,1.0f,0.0f};
        void updateVectors();

    public:
        Rotatable();
        ~Rotatable() = default;
        float getYaw() const;
        float getPitch() const;
        float getRoll() const;
        const glm::quat& getOrientation() const {return orientation;}
        const glm::vec3& getRight() const {return right;}
        const glm::vec3& getUp() const {return up;}
        void setQuat(const std::array<float,4>& arr) {}
        void rotate(float dUp,float dRight,float dRoll);
        void moveWithDirection(float dFront,float dRight,float dHeight);
    };
}