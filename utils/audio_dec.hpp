#pragma once

#include <memory>
#include <fstream>
#include <string_view>

namespace ni::utils
{
    template <typename T>
    class AudioDecoder
    {
    public:
        unsigned char* const getPCM()
        {
            return static_cast<T*>(this)->imp_getPCM();
        }

        unsigned int getPCMLength()
        {
            return static_cast<T*>(this)->imp_getPCMLength();
        }

        unsigned int getChannelCount()
        {
            return static_cast<T*>(this)->imp_getChannelCount();
        }

        unsigned int getBytesPerSec()
        {
            return static_cast<T*>(this)->imp_getBytesPerSec();
        }

        unsigned int getSimpleRate()
        {
            return static_cast<T*>(this)->imp_getSimpleRate();
        }

        unsigned int getByteRate()
        {
            return static_cast<T*>(this)->imp_getByteRate();
        }
    };
}