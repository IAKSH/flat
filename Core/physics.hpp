#pragma once

#include <array>

namespace flat
{
    class Point
    {
    private:
        float x;
        float y;
        float z;

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
        float x;
        float y;
        float z;

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

    class Rotator
    {
    private:
        Point point;
        std::array<float,4> orientation;
        std::array<float,3> right;
        std::array<float,3> up;
        
        void update_vectors();

    public:
        Rotator();
        ~Rotator();
        
        float get_rotate_yaw() const;
        float get_rotate_pitch() const;
        float get_rotate_roll() const;
        float get_position_x() const;
        float get_position_y() const;
        float get_position_z() const;
        void set_position_x(float val);
        void set_position_y(float val);
        void set_position_z(float val);
        const std::array<float,4>& get_orientation_quat()const;
        const std::array<float,3>& get_right() const;
        const std::array<float,3>& get_up() const;
        void set_quat(const std::array<float,4>& arr);
        void rotate(float d_up,float d_right,float d_roll);
        void move(float d_front,float d_right,float d_height);
    };

    class Square
    {
    private:
        Velocitor velocitor;
        Rotator rotator;
        float width;
        float height;

    public:
        Square(float x,float y,float z,float w,float h);
        Square();
        ~Square();
        
        const std::array<float,4>& get_orientation_quat() const;
        float get_square_width() const;
        float get_square_height() const;
        float get_position_x() const;
        float get_position_y() const;

        float get_position_z() const;
        float get_velocity_x() const;
        float get_velocity_y() const;
        float get_velocity_z() const;
        void set_position_x(float val);
        void set_position_y(float val);
        void set_position_z(float val);
        void set_velocity_x(float val);
        void set_velocity_y(float val);
        void set_velocity_z(float val);
        void set_square_width(float val);
        void set_square_height(float val);
        void rotate(float d_up,float d_right,float d_roll);
        void move(float d_front,float d_right,float d_height);
    };

    class Ball
    {
    private:
        Point point;
        Velocitor velocitor;
        Rotator rotator;
        float radius;

    public:
        Ball(float x,float y,float z,float r);
        Ball();
        ~Ball();

        const std::array<float,4>& get_orientation_quat() const;
        float get_radius() const;
        float get_position_x() const;
        float get_position_y() const;
        float get_position_z() const;
        float get_velocity_x() const;
        float get_velocity_y() const;
        float get_velocity_z() const;
        void set_position_x(float val);
        void set_position_y(float val);
        void set_position_z(float val);
        void set_velocity_x(float val);
        void set_velocity_y(float val);
        void set_velocity_z(float val);
        void set_radius(float val);
        void rotate(float d_up,float d_right,float d_roll);
        void move(float d_front,float d_right,float d_height);
    };

    template <typename T,typename U>
    bool collision_check(const T& t,const U& u)
    {
        // need concept
        // TODO: ...
    };
}