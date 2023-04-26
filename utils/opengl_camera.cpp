#include "opengl_camera.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtx/quaternion.hpp"

ni::utils::opengl::QuatCame::QuatCame()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
      right(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
      fov(45.0f), zoom(1.0f),
      screenWidth(800), screenHeight(600)
{
    updateCameraVectors();
}

ni::utils::opengl::QuatCame::QuatCame(const float& w,const float& h)
    : screenWidth(w),screenHeight(h),position(0.0f,0.0f,0.0f),up(0.0f,1.0f,0.0f),orientation(glm::vec3(0.0f, 0.0f, -1.0f)),fov(45.0f),
      right(glm::vec3(1.0f, 0.0f, 0.0f)),zoom(1.0f)
{
    updateCameraVectors();
}

void ni::utils::opengl::QuatCame::updateCameraVectors()
{
    // 计算当前的方向向量
    glm::vec3 direction = glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)));

    // 计算right向量和up向量
    right = glm::normalize(glm::cross(direction, up));
    up = glm::normalize(glm::cross(right, direction));
}

void ni::utils::opengl::QuatCame::setFov(const float& val)
{
    if(val < 1.0f)
    {
        ni::core::utilsLogger->error("camera's fov can't be less than 1.0f (trying to set as {})",val);
        fov = 1.0f;
    }
    else
        fov = val;
}

void ni::utils::opengl::QuatCame::move(const float& dFront,const float& dRight,const float& dHeight)
{
    position += dFront * glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)) + dRight * right + dHeight * up;
}

void ni::utils::opengl::QuatCame::rotate(const float& dUp,const float& dRight,const float& dRoll)
{
    glm::quat yawQuat = glm::angleAxis(glm::radians(dUp), right);
    glm::quat pitchQuat = glm::angleAxis(glm::radians(dRight), up);
    orientation = yawQuat * pitchQuat * orientation;
    updateCameraVectors();

    //glm::quat rollQuat = glm::angleAxis(glm::radians(dRoll), glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f))));
    //orientation = rollQuat * orientation;
    //updateCameraVectors();
}

glm::mat4 ni::utils::opengl::QuatCame::getMatrix() const
{
    glm::vec3 target = position + glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
    //rojection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    return glm::perspective(glm::radians(fov), (float)screenWidth / screenHeight, 0.1f, 2000.0f) * glm::lookAt(position, target, up);
}

ni::utils::opengl::EulerCamera::EulerCamera(const float& w,const float& h)
    : viewWidth(w), viewHeight(h),
    right(0.0f,1.0f,0.0f),up(0.0f,0.0f,1.0f),
    pitch(-90.0f),yaw(0.0f),roll(0.0f),
    fov(45.0f)
{
    updateVectors();
}

void ni::utils::opengl::EulerCamera::updateVectors()
{
    // calculate the new Front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f,0.0f,1.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}

void ni::utils::opengl::EulerCamera::setFov(const float& val)
{
    if(val < 1.0f)
    {
        ni::core::utilsLogger->error("camera's fov can't be less than 1.0f (trying to set as {})",val);
        fov = 1.0f;
    }
    else
        fov = val;
}

void ni::utils::opengl::EulerCamera::move(const float& dFront,const float& dRight,const float& dHeight)
{
    position += front * dFront;
    position += right * dRight;
    position += up * dHeight;
}

void ni::utils::opengl::EulerCamera::rotate(const float& dUp,const float& dRight,const float& dRoll)
{
    yaw += dRight;
    pitch += dUp;
    roll += dRoll;

    if (pitch < 0.1f)
        pitch = 0.1f;
    else if (pitch > 179.9f)
        pitch = 179.9f;

    updateVectors();
}

glm::mat4 ni::utils::opengl::EulerCamera::getMatrix() const
{
    return glm::perspective(glm::radians(fov), (float)viewWidth / viewHeight, 0.1f, 2000.0f) * glm::lookAt(position, position + front, up);
}
