#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "../utils/disable_copy.hpp"

namespace ni::core
{
	class Mixer : public utils::DisableCopy
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