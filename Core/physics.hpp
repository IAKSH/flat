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

        virtual float get_position_x() const;
        virtual float get_position_y() const;
        virtual float get_position_z() const;
        virtual void set_position_x(float val);
        virtual void set_position_y(float val);
        virtual void set_position_z(float val);
    };

    class Velocitor
    {
    private:
        std::array<float,3> xyz;

    public:
        Velocitor();
        Velocitor(float x,float y,float z);

        virtual float get_velocity_x() const;
        virtual float get_velocity_y() const;
        virtual float get_velocity_z() const;
        virtual void set_velocity_x(float val);
        virtual void set_velocity_y(float val);
        virtual void set_velocity_z(float val);
    };

    class Rotatable : virtual public Point
    {
    private:
        std::array<float,4> orientation;
        std::array<float,3> right;
        std::array<float,3> up;
        
        virtual void update_vectors();

    public:
        Rotatable();
        ~Rotatable();
        
        virtual float get_yaw() const;
        virtual float get_pitch() const;
        virtual float get_roll() const;
        virtual const std::array<float,4>& get_orientation() const {return orientation;}
        virtual const std::array<float,3>& get_right() const {return right;}
        virtual const std::array<float,3>& get_up() const {return up;}
        virtual void set_quat(const std::array<float,4>& arr);
        virtual void rotate(float d_up,float d_right,float d_roll);
        virtual void move_with_direction(float d_front,float d_right,float d_height);
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
        
        virtual float get_width() const;
        virtual float get_height() const;
        virtual void set_width(float val);
        virtual void set_height(float val);
    };

    class Ball : public Rotatable, public Velocitor
    {
    private:
        float radius;

    public:
        Ball(float x,float y,float z,float r);
        Ball();
        ~Ball();

        virtual float get_radius() const;
        virtual void set_radius(float val);
    };

    template <typename T,typename U>
    bool collision_check(const T& t,const U& u)
    {
        // need concept
        // TODO: ...
    };
}