#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <quick_al/vec.hpp>

namespace quick3d::al
{
	namespace Listener
	{
		// modify basical attrib
		void set_position(const Vec3& vec) noexcept;
		void set_position(ALfloat x, ALfloat y, ALfloat z) noexcept;
		void set_velocity(const Vec3& vec) noexcept;
		void set_velocity(ALfloat x, ALfloat y, ALfloat z) noexcept;
		void set_orientation(const Vec3& front, const Vec3& up) noexcept;
		void set_orientation(ALfloat front_x, ALfloat front_y, ALfloat front_z, ALfloat up_x, ALfloat up_y, ALfloat up_z) noexcept;
		void set_gain(ALfloat gain) noexcept;

		// modify Distance Attenuation
		void set_max_distance(ALfloat distance) noexcept;
		void set_min_distance(ALfloat distance) noexcept;
		void set_rolloff_factor(ALfloat factor) noexcept;

		// modify Environmental Properties
		void set_room_rolloff_factor(ALfloat factor) noexcept;
		void set_cone_outer_gain_hf(ALfloat gain_hf) noexcept;

		// get basical attrib
		Vec3 get_position() noexcept;
		Vec3 get_velocity() noexcept;
		// return forward vec and upward vec
		std::array<Vec3, 2> get_orientation() noexcept;
		ALfloat get_gain() noexcept;

		// get Distance Attenuation
		ALfloat get_max_distance() noexcept;
		ALfloat get_min_distance() noexcept;
		ALfloat get_rolloff_factor() noexcept;

		// get Environmental Properties
		ALfloat get_room_rolloff_factor() noexcept;
		ALfloat get_cone_outer_gain_hf() noexcept;
	}
}