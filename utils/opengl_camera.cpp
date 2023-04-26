#include "opengl_camera.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtx/quaternion.hpp"

ni::utils::opengl::FPSCamera::FPSCamera()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
      right(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
      fov(45.0f), zoom(1.0f),
      screenWidth(800), screenHeight(600)
{
    updateCameraVectors();
}

ni::utils::opengl::FPSCamera::FPSCamera(const float& w,const float& h)
    : screenWidth(w),screenHeight(h),position(0.0f,0.0f,0.0f),up(0.0f,1.0f,0.0f),orientation(glm::vec3(0.0f, 0.0f, -1.0f)),fov(45.0f),
      right(glm::vec3(1.0f, 0.0f, 0.0f)),zoom(1.0f)
{
    updateCameraVectors();
}

void ni::utils::opengl::FPSCamera::updateCameraVectors()
{
    // 计算当前的方向向量
    glm::vec3 direction = glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)));

    // 计算right向量和up向量
    right = glm::normalize(glm::cross(direction, up));
    up = glm::normalize(glm::cross(right, direction));
}

void ni::utils::opengl::FPSCamera::setFov(const float& val)
{
    if(val < 1.0f)
    {
        ni::core::utilsLogger->error("camera's fov can't be less than 1.0f (trying to set as {})",val);
        fov = 1.0f;
    }
    else
        fov = val;
}

void ni::utils::opengl::FPSCamera::move(const float& dFront,const float& dRight,const float& dHeight)
{
    position += dFront * glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)) + dRight * right + dHeight * up;
}

void ni::utils::opengl::FPSCamera::rotate(const float& dUp,const float& dRight,const float& dRoll)
{
    glm::quat yawQuat = glm::angleAxis(glm::radians(dUp), right);
    glm::quat pitchQuat = glm::angleAxis(glm::radians(dRight), up);
    orientation = yawQuat * pitchQuat * orientation;
    updateCameraVectors();

    //glm::quat rollQuat = glm::angleAxis(glm::radians(dRoll), glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f))));
    //orientation = rollQuat * orientation;
    //updateCameraVectors();
}

glm::mat4 ni::utils::opengl::FPSCamera::getViewMatrix() const
{
    glm::vec3 target = position + glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
    //rojection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    return glm::perspective(glm::radians(fov), (float)screenWidth / screenHeight, 0.1f, 2000.0f) * glm::lookAt(position, target, up);
}