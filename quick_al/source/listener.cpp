#include <quick_al/listener.hpp>
#include <AL/alext.h>

// generated by AI
// TODO: need to be tested

namespace quick3d::al
{
	namespace Listener
	{
		Vec3 get_position() noexcept
		{
			Vec3 position;
			alGetListenerfv(AL_POSITION, position.data());
			return position;
		}

		Vec3 get_velocity() noexcept
		{
			Vec3 velocity;
			alGetListenerfv(AL_VELOCITY, velocity.data());
			return velocity;
		}

		std::array<Vec3,2> get_orientation() noexcept
		{
			std::array<Vec3,2> orientation;
			alGetListenerfv(AL_ORIENTATION, orientation[0].data());
			alGetListenerfv(AL_ORIENTATION + 3, orientation[1].data());
			return orientation;
		}

		ALfloat get_gain() noexcept
		{
			ALfloat gain;
			alGetListenerf(AL_GAIN, &gain);
			return gain;
		}

		void set_max_distance(ALfloat distance) noexcept
		{
			alListenerf(AL_MAX_DISTANCE, distance);
		}

		void set_min_distance(ALfloat distance) noexcept
		{
			alListenerf(AL_REFERENCE_DISTANCE, distance);
		}

		void set_rolloff_factor(ALfloat factor) noexcept
		{
			alListenerf(AL_ROLLOFF_FACTOR, factor);
		}

		void set_room_rolloff_factor(ALfloat factor) noexcept
		{
			alListenerf(AL_ROOM_ROLLOFF_FACTOR, factor);
		}

		void set_cone_outer_gain_hf(ALfloat gain_hf) noexcept
		{
			alListenerf(AL_CONE_OUTER_GAINHF, gain_hf);
		}

		void set_position(const Vec3& vec) noexcept
		{
			alListenerfv(AL_POSITION, vec.data());
		}

		void set_position(ALfloat x, ALfloat y, ALfloat z) noexcept
		{
			alListener3f(AL_POSITION, x, y, z);
		}

		void set_velocity(const Vec3& vec) noexcept
		{
			alListenerfv(AL_VELOCITY, vec.data());
		}

		void set_velocity(ALfloat x, ALfloat y, ALfloat z) noexcept
		{
			alListener3f(AL_VELOCITY, x, y, z);
		}

		void set_orientation(const Vec3& front, const Vec3& up) noexcept
		{
			std::array<ALfloat, 6> arr;
			for (int i = 0; i < 3; i++)
				arr[i] = front[i];
			for (int i = 3; i < 6; i++)
				arr[i] = up[i - 3];
			alListenerfv(AL_ORIENTATION, arr.data());
		}

		void set_orientation(ALfloat front_x, ALfloat front_y, ALfloat front_z, ALfloat up_x, ALfloat up_y, ALfloat up_z) noexcept
		{
			std::array<ALfloat, 6> arr{front_x, front_y, front_z, up_x, up_y, up_z};
			alListenerfv(AL_ORIENTATION, arr.data());
		}

		void set_gain(ALfloat gain) noexcept
		{
			alListenerf(AL_GAIN, gain);
		}

		ALfloat get_max_distance() noexcept
		{
			ALfloat maxDistance;
			alGetListenerf(AL_MAX_DISTANCE, &maxDistance);
			return maxDistance;
		}

		ALfloat get_min_distance() noexcept
		{
			ALfloat minDistance;
			alGetListenerf(AL_REFERENCE_DISTANCE, &minDistance);
			return minDistance;
		}

		ALfloat get_rolloff_factor() noexcept
		{
			ALfloat rolloffFactor;
			alGetListenerf(AL_ROLLOFF_FACTOR, &rolloffFactor);
			return rolloffFactor;
		}

		ALfloat get_room_rolloff_factor() noexcept
		{
			ALfloat rolloffFactor;
			alGetListenerf(AL_ROOM_ROLLOFF_FACTOR, &rolloffFactor);
			return rolloffFactor;
		}

		ALfloat get_cone_outer_gain_hf() noexcept
		{
			ALfloat outerGainHF;
			alGetListenerf(AL_CONE_OUTER_GAINHF, &outerGainHF);
			return outerGainHF;
		}
	}
}