#pragma once

#include <array>

namespace flat
{
    class Point
    {
    private:
        std::array<float,3> xyz;

    public:
        Point()
            : xyz{0.0f,0.0f,0.0f}
        {}

        Point(float x,float y,float z)
            : xyz{x,y,z}
        {}

        float get_position_x() const {return xyz[0];}
        float get_position_y() const {return xyz[1];}
        float get_position_z() const {return xyz[2];}
        void set_position_x(float val) {xyz[0] = val;}
        void set_position_y(float val) {xyz[1] = val;}
        void set_position_z(float val) {xyz[2] = val;}
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
}