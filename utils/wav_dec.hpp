#pragma once

#include "audio_dec.hpp"

#include <memory>
#include <fstream>
#include <string_view>

namespace ni::utils
{
    class WavDecoder : public AudioDecoder<WavDecoder>
    {
    private:
        std::ifstream ifs;
        std::unique_ptr<unsigned char[]> pcm;

        struct WavStructure
        {
            char chunkID[4];
            uint32_t chunkSize;
            char format[4];
            char subchunk1ID[4];
            uint32_t subchunk1Size;
            uint16_t audioFormat;
            uint16_t numChannels;
            uint32_t sampleRate;
            uint32_t byteRate;
            uint16_t blockAlign;
            uint16_t bitsPerSample;
            char subchunk2ID[4];
            uint32_t subchunk2Size;
        } structure;
        
        void load();

    public:
        WavDecoder(std::string_view path);
        WavDecoder(WavDecoder&) = delete;
        ~WavDecoder() = default;

        unsigned char* const imp_getPCM() { return pcm.get(); }
        const auto& imp_getPCMLength() { return structure.subchunk2Size; }
        const auto& imp_getChannelCount() { return structure.numChannels; }
        const auto& imp_getBytesPerSec() { return structure.bitsPerSample; }
        const auto& imp_getSimpleRate() { return structure.sampleRate; }
        const auto& imp_getByteRate() { return structure.byteRate; }
    };
}