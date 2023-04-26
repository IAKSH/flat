#pragma once

#include "glm/fwd.hpp"
#include "physics.hpp"
#include "../core/loggers.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ni::utils::opengl
{
    class QuatCame
    {
    private:
        glm::vec3 position;
        glm::quat orientation; // 使用四元数存储方向向量
        glm::vec3 right;
        glm::vec3 up;

        float fov;
        float zoom;

        int screenWidth;
        int screenHeight;

        void updateCameraVectors();

    public:
        QuatCame();
        QuatCame(const float& w,const float& h);
        ~QuatCame() = default;

        const float& getPositionX() {return position[0];}
        const float& getPositionY() {return position[1];}
        const float& getPositionZ() {return position[2];}
        const float& getYaw() {return glm::eulerAngles(orientation)[0];}
        const float& getPitch() {return glm::eulerAngles(orientation)[1];}
        const float& getRoll() {return glm::eulerAngles(orientation)[2];}
        const float& getZoom() {return zoom;}
        const float& getFOV() {return fov;}
        glm::mat4 getMatrix() const;

        void setPositionX(const float& val) {position[0] = val;}
        void setPositionY(const float& val) {position[1] = val;}
        void setPositionZ(const float& val) {position[2] = val;}
        //void setYaw(const float& val) {recordedYaw = val;}
        //void setPitch(const float& val) {recordedPitch = val;}
        void setZoom(const float& val);
        void setFov(const float& val);

        void move(const float& dFront,const float& dRight,const float& dHeight);
        void rotate(const float& dUp,const float& dRight,const float& dRoll);
    };

    class EulerCamera
    {
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        float pitch,yaw,roll;
        float fov;
        const int viewWidth,viewHeight;
        void updateVectors();

    public:
        EulerCamera(const float& w,const float& h);
        ~EulerCamera() = default;
        const float& getPositionX() {return position[0];}
        const float& getPositionY() {return position[1];}
        const float& getPositionZ() {return position[2];}
        const float& getYaw() {return yaw;}
        const float& getPitch() {return pitch;}
        const float& getRoll() {return roll;}
        const float& getFOV() {return fov;}
        glm::mat4 getMatrix() const;

        void setPositionX(const float& val) {position[0] = val;}
        void setPositionY(const float& val) {position[1] = val;}
        void setPositionZ(const float& val) {position[2] = val;}
        void setYaw(const float& val) {yaw = val;}
        void setPitch(const float& val) {pitch = val;}
        void setRoll(const float& val) {roll = val;}
        void setFov(const float& val);

        void move(const float& dFront,const float& dRight,const float& dHeight);
        void rotate(const float& dUp,const float& dRight,const float& dRoll);
    };

    using Camera = QuatCame;
}