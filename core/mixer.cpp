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

	alDistanceModel(AL_LINEAR_DISTANCE);
	ALfloat listenerPosition[] = {0.0f, 0.0f, 1.0f};
	alListenerfv(AL_POSITION, listenerPosition);
	ALfloat listenerOrientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
	alListenerfv(AL_ORIENTATION, listenerOrientation);
}

void ni::core::Mixer::release()
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}