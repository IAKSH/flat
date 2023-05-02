#include "openal_mixer.hpp"
#include "AL/al.h"
#include "AL/alc.h"
#include "loggers.hpp"
#include <exception>

ni::core::openal::Mixer::Mixer()
{
    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device,nullptr);
    alcMakeContextCurrent(context);

    ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        coreLogger->critical("OpenAL error: {}",alGetString(error));
        std::terminate();
    }

    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
}

ni::core::openal::Mixer::~Mixer()
{
    alcDestroyContext(context);
    alcCloseDevice(device);
}

std::array<float,3> ni::core::openal::Listener::getPositionVec()
{
    std::array<float,3> arr;
    alGetListenerfv(AL_POSITION,arr.data());
    return arr;
}

std::array<float,3> ni::core::openal::Listener::getVelocityVec()
{
    std::array<float,3> arr;
    alGetListenerfv(AL_VELOCITY,arr.data());
    return arr;
}

std::array<float,3> ni::core::openal::Listener::getOrientationVec()
{
    std::array<float,3> arr;
    alGetListenerfv(AL_ORIENTATION,arr.data());
    return arr;
}

void ni::core::openal::Listener::setPositionX(const float& val)
{
    auto position = getPositionVec();
    position[0] = val;
    alListenerfv(AL_POSITION,position.data());
}

void ni::core::openal::Listener::setPositionY(const float& val)
{
    auto position = getPositionVec();
    position[1] = val;
    alListenerfv(AL_POSITION,position.data());
}

void ni::core::openal::Listener::setPositionZ(const float& val)
{
    auto position = getPositionVec();
    position[2] = val;
    alListenerfv(AL_POSITION,position.data());
}

void ni::core::openal::Listener::setVelocityX(const float& val)
{
    auto velocity = getVelocityVec();
    velocity[0] = val;
    alListenerfv(AL_VELOCITY,velocity.data());
}

void ni::core::openal::Listener::setVelocityY(const float& val)
{
    auto velocity = getVelocityVec();
    velocity[1] = val;
    alListenerfv(AL_VELOCITY,velocity.data());
}

void ni::core::openal::Listener::setVelocityZ(const float& val)
{
    auto velocity = getVelocityVec();
    velocity[2] = val;
    alListenerfv(AL_VELOCITY,velocity.data());
}

void ni::core::openal::Listener::setOrientationX(const float& val)
{
    auto orientation = getOrientationVec();
    orientation[0] = val;
    alListenerfv(AL_ORIENTATION,orientation.data());
}

void ni::core::openal::Listener::setOrientationY(const float& val)
{
    auto orientation = getOrientationVec();
    orientation[1] = val;
    alListenerfv(AL_ORIENTATION,orientation.data());
}

void ni::core::openal::Listener::setOrientationZ(const float& val)
{
    auto orientation = getOrientationVec();
    orientation[2] = val;
    alListenerfv(AL_ORIENTATION,orientation.data());
}

float ni::core::openal::Listener::getPositionX()
{
    return getPositionVec()[0];
}

float ni::core::openal::Listener::getPositionY()
{
    return getPositionVec()[1];
}

float ni::core::openal::Listener::getPositionZ()
{
    return getPositionVec()[2];
}

float ni::core::openal::Listener::getVelocityX()
{
    return getVelocityVec()[0];
}

float ni::core::openal::Listener::getVelocityY()
{
    return getVelocityVec()[1];
}

float ni::core::openal::Listener::getVelocityZ()
{
    return getVelocityVec()[2];
}

float ni::core::openal::Listener::getOrientationX()
{
    return getOrientationVec()[0];
}

float ni::core::openal::Listener::getOrientationY()
{
    return getOrientationVec()[1];
}

float ni::core::openal::Listener::getOrientationZ()
{
    return getOrientationVec()[2];
}
