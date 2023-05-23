#pragma once

#include <array>
#include "glm/gtc/quaternion.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace flat
{
    class Rotator
    {
    private:
        std::array<float,4> orientation;
        std::array<float,3> right;
        std::array<float,3> up;

    public:
        Rotator();
        ~Rotator();
        
        float get_yaw() const;
        float get_pitch() const;
        float get_roll() const;
        const std::array<float,4>& get_orientation_quat() const {return orientation;}
        const std::array<float,3>& get_right_vec() const {return right;}
        const std::array<float,3>& get_up_vec() const {return up;}
        void set_orientation_quat(const std::array<float,4>& arr) {orientation = arr;}
        void set_right_vec(const std::array<float,3>& arr) {right = arr;}
        void set_up_vec(const std::array<float,3>& arr) {up = arr;}
    };

    template <typename T>
    concept WithOrientationQuat = requires(T t,const std::array<float,4>& quat)
    {
        {t.get_orientation_quat()} -> std::same_as<const std::array<float,4>&>;
        {t.set_orientation_quat(quat)} -> std::same_as<void>;
    };

    template <typename T>
    concept WithRightVec = requires(T t,const std::array<float,3>& vec)
    {
        {t.get_right_vec()} -> std::same_as<const std::array<float,3>&>;
        {t.set_right_vec(vec)} -> std::same_as<void>;
    };

    template <typename T>
    concept WithUpVec = requires(T t,const std::array<float,3>& vec)
    {
        {t.get_up_vec()} -> std::same_as<const std::array<float,3>&>;
        {t.set_up_vec(vec)} -> std::same_as<void>;
    };

    template <typename T>
    requires(WithOrientationQuat<T>
        && WithRightVec<T>
        && WithUpVec<T>)
    void update_rotate_vector(T& t)
    {
        auto orientation = t.get_orientation_quat();
        auto right = t.get_right_vec();
        auto up = t.get_up_vec();

        glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
        glm::vec3 vec_right(right[0],right[1],right[2]);
        glm::vec3 vec_up(up[0],up[1],up[2]);

        glm::vec3 direction = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
        vec_right = glm::normalize(glm::cross(direction, vec_up));
        vec_up = glm::normalize(glm::cross(vec_right, direction));

        t.set_orientation_quat({quat[0],quat[1],quat[2],quat[3]});
        t.set_right_vec({vec_right[0],vec_right[1],vec_right[2]});
        t.set_up_vec({vec_up[0],vec_up[1],vec_up[2]});
    }
    
    template <typename T>
    requires(WithOrientationQuat<T>
        && WithRightVec<T>
        && WithUpVec<T>)
    void rotate(T& t,float d_up,float d_right,float d_roll)
    {
        auto orientation = t.get_orientation_quat();
        auto right = t.get_right_vec();
        auto up = t.get_up_vec();

        glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
        glm::vec3 vec_right(right[0],right[1],right[2]);
        glm::vec3 vec_up(up[0],up[1],up[2]);

        glm::quat yaw_quat = glm::angleAxis(glm::radians(d_up),vec_right);
        glm::quat pitch_quat = glm::angleAxis(glm::radians(-d_right),vec_up);
        quat = yaw_quat * pitch_quat * quat;

        orientation = {quat[0],quat[1],quat[2],quat[3]};
        right = {vec_right[0],vec_right[1],vec_right[2]};
        up = {vec_up[0],vec_up[1],vec_up[2]};

        update_rotate_vector(t);
    }

    template <typename T>
    concept WithPosition = requires(T t,const std::array<float,3>& arr)
    {
        {t.get_position()} -> std::same_as<const std::array<float,3>&>;
        {t.set_position(arr)} -> std::same_as<void>;
    };

    template <typename T>
    concept WithVelocity = requires(T t,const std::array<float,3>& arr)
    {
        {t.get_velocity()} -> std::same_as<const std::array<float,3>&>;
        {t.set_velocity(arr)} -> std::same_as<void>;
    };

    template <typename T>
    requires(WithOrientationQuat<T>
        && WithRightVec<T>
        && WithUpVec<T>
        && WithPosition<T>)
    void move_by_orientation(const T& t,float d_front,float d_right,float d_height)
    {
        auto orientation = t.get_orientation_quat();
        auto right = t.get_right_vec();
        auto up = t.get_up_vec();

        glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
        glm::vec3 vec_right(right[0],right[1],right[2]);
        glm::vec3 vec_up(up[0],up[1],up[2]);
        glm::vec3 position(t.get_position_x(),t.get_position_y(),t.get_position_z());

        position += d_front * glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)) + d_right * vec_right + d_height * vec_up;

        t.set_position_x(position[0]);
        t.set_position_y(position[1]);
        t.set_position_z(position[2]);
    }

    template <typename T>
    concept Square = WithOrientationQuat<T>
        && WithRightVec<T>
        && WithUpVec<T>
        && WithPosition<T>
        && requires(T t,float w,float h)
    {

        {t.get_square_width()} -> std::same_as<float>;
        {t.get_square_height()} -> std::same_as<float>;
        {t.set_square_width(w)} -> std::same_as<void>;
        {t.set_square_height(h)} -> std::same_as<void>;
    };

    template <typename T>
    concept Ball = WithOrientationQuat<T>
        && WithRightVec<T>
        && WithUpVec<T>
        && WithPosition<T>
        && requires(T t,float r)
    {
        {t.get_ball_radius()} -> std::same_as<float>;
        {t.set_ball_radius(r)} -> std::same_as<void>;
    };

    template <typename T>
    concept PhysicsModel = (Ball<T> || Square<T>) && WithVelocity<T>;

    template <typename T,typename U>
    requires(PhysicsModel<T> && PhysicsModel<U>)
    bool collision_check(const T& t,const U& u)
    {
        // TODO: ...
    };
}