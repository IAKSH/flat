#include "mixer.hpp"

#include "../utils/logger.hpp"

ni::core::Mixer::Mixer()
{
	initialize();
}

ni::core::Mixer::~Mixer()
{
	release();
}

void ni::core::Mixer::initialize()
{
	device = alcOpenDevice(nullptr);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);

	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		utils::coreLogger()->critical("OpenAL error: {}", alGetString(error));
		abort();
	}
}

void ni::core::Mixer::release()
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}