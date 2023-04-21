#include "mixer.hpp"
#include "loggers.hpp"
#include <exception>

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
		coreLogger->critical("OpenAL error: {}", alGetString(error));
		std::terminate();
	}

	alDistanceModel(AL_LINEAR_DISTANCE);
	ALfloat listenerPosition[] = {0.0f, 0.0f, 0.0f};
	alListenerfv(AL_POSITION, listenerPosition);
	ALfloat listenerOrientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
	alListenerfv(AL_ORIENTATION, listenerOrientation);

	// set global distance model to inverse
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
}

void ni::core::Mixer::release()
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}