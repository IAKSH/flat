#pragma once

#include "../utils/template.hpp"
#include <AL/al.h>
#include <AL/alc.h>

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