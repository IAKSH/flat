#include "opengl_camera.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtx/quaternion.hpp"

ni::utils::opengl::QuatCamera::QuatCamera()
    : fov(45.0f), zoom(1.0f),
      screenWidth(800), screenHeight(600)
{
    //position(glm::vec3(0.0f, 0.0f, 0.0f)), orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
    //  right(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
}

ni::utils::opengl::QuatCamera::QuatCamera(const float& w,const float& h)
    : screenWidth(w),screenHeight(h),zoom(1.0f)
{
    //position(0.0f,0.0f,0.0f),up(0.0f,1.0f,0.0f),orientation(glm::vec3(0.0f, 0.0f, -1.0f)),fov(45.0f),
    //  right(glm::vec3(1.0f, 0.0f, 0.0f))
}

void ni::utils::opengl::QuatCamera::setFov(const float& val)
{
    if(val < 1.0f)
    {
        ni::core::utilsLogger->error("camera's fov can't be less than 1.0f (trying to set as {})",val);
        fov = 1.0f;
    }
    else
        fov = val;
}

glm::mat4 ni::utils::opengl::QuatCamera::getMatrix() const
{
    glm::vec3 position(getPositionX(),getPositionY(),getPositionZ());

    glm::vec3 target = position + glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    return glm::perspective(glm::radians(fov), (float)screenWidth / screenHeight, 0.1f, 2000.0f) * glm::lookAt(position, target, getUp());
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
