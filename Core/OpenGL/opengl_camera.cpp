// [ *This file has been abandoned!* ]

//#include "opengl_camera.hpp"

//flat::opengl::Camera::Camera()
//    : fov(45.0f),zoom(1.0f),view_width(800),view_height(600)
//{}
//
//flat::opengl::Camera::Camera(float w,float h)
//    : fov(45.0f),zoom(1.0f),view_width(w),view_height(h)
//{}
//
//flat::opengl::Camera::~Camera() = default;
//
//void flat::opengl::Camera::set_fov(float val)
//{
//    if(val < 1.0f)
//    {
//        misc::main_logger->error("camera's fov can't be less than 1.0f (trying to set as {})",val);
//        fov = 1.0f;
//    }
//    else
//        fov = val;
//}
//
//glm::mat4 flat::opengl::Camera::get_matrix() const
//{
//    glm::vec3 position(get_position_x(),get_position_y(),get_position_z());
//    glm::vec3 vec_up(get_up()[0],get_up()[1],get_up()[2]);
//    glm::quat quat(get_orientation()[0],get_orientation()[1],get_orientation()[2],get_orientation()[3]);
//
//    glm::vec3 target = position + glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f));
//    return glm::perspective(glm::radians(fov), (float)view_width / view_height, 0.1f, 2000.0f) * glm::lookAt(position, target, vec_up);
//}