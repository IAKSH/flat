#pragma once

#include <quick_al/vec.hpp>
#include <quick_al/buffer.hpp>

namespace quick3d::al
{
	class Source
	{
	private:
        Buffer* binding_buffer;
		ALuint source_id;

        void create_source() noexcept;
        void delete_source() noexcept;

	public:
		Source() noexcept;
        Source(Buffer& buffer) noexcept;
        Source(Source&) = delete;
		~Source() noexcept;

        ALuint get_source_id() noexcept;

        void set_source_position(const Vec3& vec) noexcept;
        void set_source_position(ALfloat x, ALfloat y, ALfloat z) noexcept;
        void set_source_velocity(const Vec3& vec) noexcept;
        void set_source_velocity(ALfloat x, ALfloat y, ALfloat z) noexcept;
        void set_source_orientation(const Vec3& front, const Vec3& up) noexcept;
        void set_source_orientation(ALfloat front_x, ALfloat front_y, ALfloat front_z, ALfloat up_x, ALfloat up_y, ALfloat up_z);
        void set_source_direction(const Vec3& vec);
        void set_source_direction(ALfloat x, ALfloat y, ALfloat z);
        void set_source_gain(ALfloat gain) noexcept;
        void set_source_pitch(ALfloat pitch) noexcept;
        void set_source_looping(ALboolean looping) noexcept;
        void set_source_relative(ALboolean relative) noexcept;
        void set_source_reference_distance(ALfloat distance) noexcept;
        void set_source_max_distance(ALfloat distance) noexcept;
        void set_rolloff_factor(ALfloat factor) noexcept;
        void set_cone_inner_angle(ALfloat angle) noexcept;
        void set_cone_outer_angle(ALfloat angle) noexcept;
        void set_cone_outer_gain(ALfloat gain) noexcept;

        Vec3 get_source_position() const noexcept;
        Vec3 get_source_velocity() const noexcept;
        std::array<Vec3,2> get_source_orientation() const noexcept;
        Vec3 get_source_direction() const noexcept;
        ALfloat get_source_gain() const noexcept;
        ALfloat get_source_pitch() const noexcept;
        ALboolean get_source_looping() const noexcept;
        ALboolean get_source_relative() const noexcept;
        ALfloat get_source_reference_distance() const noexcept;
        ALfloat get_source_max_distance() const noexcept;
        ALfloat get_rolloff_factor() const noexcept;
        ALfloat get_cone_inner_angle() const noexcept;
        ALfloat get_cone_outer_angle() const noexcept;
        ALfloat get_cone_outer_gain() const noexcept;

        ALboolean is_playing() const noexcept;
        Buffer* get_binding_buffer() noexcept;
        void bind_buffer(Buffer& buffer) noexcept;
        void play_sound(Buffer& buffer) noexcept;
        void play_sound() noexcept(false);
	};
}