#include "audio_source.hpp"
#include "al.h"

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
    alGenSources(1, &sourceID);
}

void ni::utils::AudioSource::release()
{
    alDeleteSources(1, &sourceID);
}
