#include "openal_source.hpp"
#include "AL/al.h"

flat::openal::Source::Source()
{
    alGenSources(1,&source_id);
    alSourcei(source_id,AL_SOURCE_TYPE,AL_STREAMING);
    alSourcef(source_id,AL_REFERENCE_DISTANCE,100.0f);
    alSourcef(source_id,AL_ROLLOFF_FACTOR,1.0f);
    alSourcei(source_id,AL_SOURCE_RELATIVE,AL_FALSE);
}

flat::openal::Source::~Source()
{
    alDeleteSources(1,&source_id);
}