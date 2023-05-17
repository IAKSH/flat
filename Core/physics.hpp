#pragma once

#include <array>

namespace flat
{
    class Point
    {
    private:
        std::array<float,3> xyz;

    public:
        Point();
        Point(float x,float y,float z);

        float get_position_x() const;
        float get_position_y() const;
        float get_position_z() const;
        void set_position_x(float val);
        void set_position_y(float val);
        void set_position_z(float val);
    };

    class Velocitor
    {
    private:
        std::array<float,3> xyz;

    public:
        Velocitor();
        Velocitor(float x,float y,float z);

        float get_velocity_x() const;
        float get_velocity_y() const;
        float get_velocity_z() const;
        void set_velocity_x(float val);
        void set_velocity_y(float val);
        void set_velocity_z(float val);
    };

    class Rotatable : public Point
    {
    private:
        std::array<float,4> orientation;
        std::array<float,3> right;
        std::array<float,3> up;
        
        void update_vectors();

    public:
        Rotatable();
        ~Rotatable();
        
        float get_yaw() const;
        float get_pitch() const;
        float get_roll() const;
        const auto& get_orientation() const {return orientation;}
        const auto& get_right() const {return right;}
        const auto& get_up() const {return up;}
        void set_quat(const std::array<float,4>& arr);
        void rotate(float d_up,float d_right,float d_roll);
        void move_with_direction(float d_front,float d_right,float d_height);
    };

    class Rectangle : public Rotatable, public Velocitor
    {
    private:
        float width;
        float height;

    public:
        Rectangle(float x,float y,float z,float w,float h);
        Rectangle();
        ~Rectangle();
        
        float get_width() const;
        float get_height() const;
        void set_width(float val);
        void set_height(float val);
    };

    class Ball : public Rotatable, public Velocitor
    {
    private:
        float radius;

    public:
        Ball(float x,float y,float z,float r);
        Ball();
        ~Ball();

        float get_radius() const;
        void set_radius(float val);
    };

    template <typename T,typename U>
    bool collision_check(const T& t,const U& u)
    {
        // need concept
        // TODO: ...
    };
}