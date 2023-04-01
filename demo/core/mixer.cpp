#include "mixer.hpp"

#include "log.hpp"

flat::core::Mixer::Mixer()
{
	initialize();
}

flat::core::Mixer::~Mixer()
{
	release();
}

void flat::core::Mixer::initialize()
{
	device = alcOpenDevice(nullptr);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);

	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		LOG_CRITICAL("OpenAL error: {}", alGetString(error));
		abort();
	}
}

void flat::core::Mixer::release()
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}