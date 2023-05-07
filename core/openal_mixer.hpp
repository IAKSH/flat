#pragma once

#include "mixer.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <array>

namespace ni::core::openal
{
    class Listener : public core::DisableCopy
    {
    private:
        std::array<float,3> getPositionVec();
        std::array<float,3> getVelocityVec();
        std::array<float,3> getOrientationVec();

    public:
        Listener() = default;
        ~Listener() = default;
        void setPositionX(const float& val);
        void setPositionY(const float& val);
        void setPositionZ(const float& val);
        void setVelocityX(const float& val);
        void setVelocityY(const float& val);
        void setVelocityZ(const float& val);
        void setOrientationX(const float& val);
        void setOrientationY(const float& val);
        void setOrientationZ(const float& val);
        float getPositionX();
        float getPositionY();
        float getPositionZ();
        float getVelocityX();
        float getVelocityY();
        float getVelocityZ();
        float getOrientationX();
        float getOrientationY();
        float getOrientationZ();
    };

    class Mixer : public ni::core::Mixer<Mixer> 
    {
    private:
        ALCdevice* device;
        ALCcontext* context;
        Listener listener;

    public:
        Mixer();
        ~Mixer();
        Listener& getListener() {return listener;}
        ALCdevice* getDevice() {return device;}
        ALCcontext* getContext() {return context;}
    };
}