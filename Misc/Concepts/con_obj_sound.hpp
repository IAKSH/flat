#pragma once

#include <concepts>

namespace flat::misc::concepts
{
    template <typename T>
    concept Sound = requires(T t,const unsigned char* const pcm,int sample_rate,int pcm_len)
    {
        {T(pcm,sample_rate,pcm_len)} -> std::same_as<T*>;
        {t.play()} -> std::same_as<void>;
        {t.pause()} -> std::same_as<void>;
        {t.resume()} -> std::same_as<void>;
        {t.restart()} -> std::same_as<void>;
    };
};