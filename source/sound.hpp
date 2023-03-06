#pragma once

#include <cstdint>
#include <vector>
#include <string_view>

#include <AL/al.h>
#include <AL/alc.h>

#include "physics.hpp"

namespace flat
{
	class Audio
	{
	private:
		uint32_t bufferId;
		void releaseBuffer();

	public:
		Audio();
		~Audio();
		void load(std::string_view path);
		const uint32_t &getBufferId();
	};

	class SoundSource : virtual public Physical
	{
	private:
		uint32_t sourceId;
		int sampleOffset;

	protected:
		SoundSource();
		~SoundSource();

	public:
		void initializeSoundSource();
		void updateSoundSource();
		void setSoundVolume(float volume);
		void setSoundLoopable(bool loopable);
		void playSound(Audio &audio);
		void stopSound();
		void pauseSound();
		void resumeSound();
		float getSoundVolume();
		bool getSoundLoopable();
	};

	class Listener : public Physical
	{
	private:
		ALCdevice *device;
		ALCcontext *context;

	protected:
		Listener();
		~Listener();

	public:
		void initializeListener();
		void updateListener();
	};
}