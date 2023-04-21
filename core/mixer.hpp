#pragma once

#include "template.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace ni::core
{
	class Mixer : public DisableCopy
	{
	private:
		ALCdevice* device;
		ALCcontext* context;
		void initialize();
		void release();

	public:
		Mixer();
		~Mixer();
	};
}