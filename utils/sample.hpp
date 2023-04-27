#pragma once

#include <memory>
#include <string>

namespace ni::utils
{
    class Sample
    {
    private:
        int channels,sampleRate,byteRate,bitsPerSample;
        size_t pcmLen;
        std::unique_ptr<unsigned char[]> pcm;
        void loadWav(std::string_view path);
        [[deprecated("unrealized")]] void loadMp3(std::string_view path);
        [[deprecated("unrealized")]] void loadOgg(std::string_view path);

    public:
        Sample(std::string_view path);
        ~Sample() = default;
        unsigned char* const getPCM() {return pcm.get();}
        const int& getChannels() {return channels;}
        const int& getSampleRate() {return sampleRate;}
        const int& getByteRate() {return byteRate;}
        const int& getBitsPerSample() {return bitsPerSample;}
        const size_t& getPCMLen() {return pcmLen;}
    };
}