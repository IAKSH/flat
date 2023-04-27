#include "openal_source.hpp"

ni::utils::openal::Source::Source()
{
    alGenSources(1,&sourceID);
    alSourcei(sourceID,AL_SOURCE_TYPE,AL_STREAMING);
    alSourcef(sourceID,AL_REFERENCE_DISTANCE,100.0f);
    alSourcef(sourceID,AL_ROLLOFF_FACTOR,1.0f);
    alSourcei(sourceID,AL_SOURCE_RELATIVE,AL_FALSE);
}

ni::utils::openal::Source::~Source()
{
    alDeleteSources(1,&sourceID);
}
