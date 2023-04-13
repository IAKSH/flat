#include "audio_source.hpp"

ni::utils::AudioSource::AudioSource()
{
    initialize();
}

ni::utils::AudioSource::~AudioSource()
{
    release();
}

void ni::utils::AudioSource::initialize()
{
    float zero[] = {0.0f,0.0f,0.0f};
    alGenSources(1, &sourceID);
    alSourcefv(sourceID,AL_POSITION,zero);
    alSourcefv(sourceID,AL_VELOCITY,zero);
    alSourcei(sourceID,AL_SOURCE_RELATIVE,AL_FALSE);
    alSourcei(sourceID,AL_SOURCE_TYPE,AL_STREAMING);
    alSourcef(sourceID,AL_REFERENCE_DISTANCE,1.0f);
    alSourcef(sourceID,AL_MAX_DISTANCE,100.0f);
    alSourcef(sourceID,AL_ROLLOFF_FACTOR,1.0f);
}

void ni::utils::AudioSource::release()
{
    alDeleteSources(1, &sourceID);
}
