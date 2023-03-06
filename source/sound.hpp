#pragma once

#include <cstdint>
#include <vector>
#include <string_view>

#include "physics.hpp"

namespace flat
{
    class Audio
    {
    private:
        std::vector<uint32_t> bufferIds;
        void releaseBuffer();
    public:
        Audio();
        ~Audio();
        void load(std::string_view path);
        const std::vector<uint32_t>& getBufferIds();
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
		void playSound(Audio& audio);
		void stopSound();
		void pauseSound();
		void resumeSound();
		float getSoundVolume();
		bool getSoundLoopable();
	};

    class Listener : public Physical
	{
	protected:
		Listener();
		~Listener();
	public:
		void updateListener();
	};
}