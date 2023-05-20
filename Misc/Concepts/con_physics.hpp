#pragma once

#include <array>
#include <concepts>

namespace flat::misc::concepts
{
    template <typename T>
    concept Point2D = requires(T t,float f,float x,float y,float z)
    {
        {new T(x,y,z)} -> std::same_as<T*>;
        {t.get_position_x()} -> std::same_as<float>;
        {t.get_position_y()} -> std::same_as<float>;
        {t.set_position_x(f)} -> std::same_as<void>;
        {t.set_position_y(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Point3D = requires(T t,float f)
    {
        requires(Point2D<T>);
        {t.get_position_z()} -> std::same_as<float>;
        {t.set_position_z(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Velocitor2D = requires(T t,float f,float x,float y)
    {
        {new T(x,y)} -> std::same_as<T*>;
        {t.get_velocity_x()} -> std::same_as<float>;
        {t.get_velocity_y()} -> std::same_as<float>;
        {t.set_velocity_x(f)} -> std::same_as<void>;
        {t.set_velocity_y(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Velocitor3D = requires(T t,float f,float x,float y,float z)
    {
        requires(Velocitor2D<T>);
        {new T(x,y,z)} -> std::same_as<T*>;
        {t.get_velocity_z()} -> std::same_as<float>;
        {t.set_velocity_z(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Rotator2D = requires(T t,float f)
    {
        requires(Point2D<T>);
        {new T()} -> std::same_as<T*>;
        {t.get_rotate()} -> std::same_as<float>;
        {t.set_rotate(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Rotator3D = requires(T t,float up,float right,float roll,float forward,float height)
    {
        requires(Point3D<T>);
        {t.get_orientation_quat()} -> std::same_as<const std::array<float,4>&>;
        {t.rotate(up,right,roll)} -> std::same_as<void>;
        {t.move(forward,right,height)} -> std::same_as<void>;
    };

    template <typename T>
    concept Square = requires(T t,float f,float x,float y,float z,float w,float h)
    {
        requires(Velocitor3D<T>);
        requires(Rotator3D<T>);
        {T(x,y,z,w,h)} -> std::same_as<T*>;
        {t.get_square_width()} -> std::same_as<float>;
        {t.get_square_height()} -> std::same_as<float>;
        {t.set_square_width(f)} -> std::same_as<void>;
        {t.set_square_height(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept Ball = requires(T t,float f,float x,float y,float z,float r)
    {
        requires(Velocitor3D<T>);
        requires(Rotator3D<T>);
        {T(x,y,z,r)} -> std::same_as<T*>;
        {t.get_radius()} -> std::same_as<float>;
        {t.set_radius(f)} -> std::same_as<void>;
    };

    template <typename T>
    concept PhysicsModel = Ball<T> || Square<T>;
};