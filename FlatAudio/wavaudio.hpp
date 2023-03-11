#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <fstream>
#include <array>

#include <cstdint>

namespace wava
{
    class WavAudio
    {
    private:
        uint32_t buffer;
        bool loop = true;
        bool loaded = false;

        // RIFF chunk (main chunk)
        uint32_t chunkSize;
        char format[5] = {'\0'};

        // sub-chunk 1 (fmt chunk)
        uint32_t subChunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;

        // sub-chunk 2 (data)
        uint32_t subChunk2Size;
        unsigned char *data;

        int getFileCursorMark(std::ifstream &fs, std::string mark);

    public:
        WavAudio();
        WavAudio(const char *path);
        ~WavAudio();

        void load(const char *path);
        uint32_t getBuffer();
    };
}