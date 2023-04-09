#pragma once

#include <AL/al.h>
#include <al/alc.h>

namespace ni::core
{
	class Mixer
	{
	private:
		ALCdevice* device;
		ALCcontext* context;
		void initialize();
		void release();

	public:
		Mixer();
		Mixer(Mixer&) = delete;
		~Mixer();
	};
}