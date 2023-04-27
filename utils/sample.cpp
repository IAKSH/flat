#include "sample.hpp"
#include "../core/loggers.hpp"
#include "../core/template.hpp"
#include <exception>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <cstdint>

ni::utils::Sample::Sample(std::string_view path)
{
    std::string extension = std::filesystem::path(path).extension().string();
    try
    {
        if(extension == ".wav")
            loadWav(path);
        else if(extension == ".mp3")
            loadMp3(path);
        else if(extension == ".ogg")
            loadOgg(path);
        else
	    {
	    	ni::core::utilsLogger->critical("unknow extension type: {} ({})",extension,path);
	    	std::terminate();
	    }
        return;
    }
    catch(const std::exception& e)
    {
        core::utilsLogger->critical("exception catched: {}",e.what());
    }
    std::terminate();
}

template <typename T>
struct AudioDecoder : public ni::core::DisableCopy
{
    std::unique_ptr<unsigned char[]> getPCM() {return static_cast<T*>(this)->impl_getPCM();}
    unsigned int getPCMLength() {return static_cast<T*>(this)->impl_getPCMLength();}
    unsigned int getChannels() {return static_cast<T*>(this)->impl_getChannels();}
    unsigned int getBytesPerSec() {return static_cast<T*>(this)->impl_getBytesPerSec();}
    unsigned int getSampleRate() {return static_cast<T*>(this)->impl_getSampleRate();}
    unsigned int getByteRate() {return static_cast<T*>(this)->impl_getByteRate();}
    size_t getPCMLen() {return static_cast<T*>(this)->impl_getPCMLen();}
};

class WavDecoder : public AudioDecoder<WavDecoder>
{
private:
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
    }
    structure;

    void load(std::string_view path) noexcept(false)
    {
        std::ifstream ifs(path,std::ios::in | std::ios::binary);
        if(!ifs)
            throw std::runtime_error("failed to open file");

        ifs.read(reinterpret_cast<char*>(&structure), sizeof(structure));
        if (std::string(structure.chunkID, 4) != "RIFF" ||
            std::string(structure.format, 4) != "WAVE" ||
            std::string(structure.subchunk1ID, 4) != "fmt ")
        {
            throw std::runtime_error("trying to decode a non-wav file");
        }

        std::string buffer(4,'\0');
        size_t i = 0;
        while (!ifs.eof())
        {
            ifs.seekg(i++, std::ios::beg);
            ifs.read(buffer.data(), sizeof(char) * 4);
            if (buffer == "data")
            {
                structure.subchunk2ID[0] = 'd';
                structure.subchunk2ID[1] = 'a';
                structure.subchunk2ID[2] = 't';
                structure.subchunk2ID[3] = 'a';
                ifs.seekg(i + 3, std::ios::beg);
                ifs.read(reinterpret_cast<char*>(&structure.subchunk2Size), 4);

                const size_t data_size = static_cast<size_t>(structure.subchunk2Size);
                pcm = std::move(std::make_unique<unsigned char[]>(data_size));
                ifs.read(reinterpret_cast<char*>(pcm.get()), data_size);
                return;
            }
        }

        throw std::runtime_error("can't locate data chunk in WAV file");
    }

public:
    WavDecoder(std::string_view path)
    {
        try
        {
            load(path);
            return;
        }
        catch(const std::exception& e)
        {
            ni::core::utilsLogger->critical("exception catched in WavDecoder: {}",e.what());
        }
        std::terminate();
    }
    ~WavDecoder() = default;
    std::unique_ptr<unsigned char[]> impl_getPCM() { return std::move(pcm); }
    const auto& impl_getPCMLength() { return structure.subchunk2Size; }
    const auto& impl_getChannels() { return structure.numChannels; }
    const auto& impl_getBytesPerSec() { return structure.bitsPerSample; }
    const auto& impl_getSampleRate() { return structure.sampleRate; }
    const auto& impl_getByteRate() { return structure.byteRate; }
    const auto& impl_getPCMLen() { return structure.subchunk2Size; }
};

void ni::utils::Sample::loadWav(std::string_view path)
{
    AudioDecoder<WavDecoder>&& decoder = WavDecoder(path);
    pcm = decoder.getPCM();
    channels = decoder.getChannels();
    sampleRate = decoder.getSampleRate();
    byteRate = decoder.getByteRate();
    bitsPerSample = decoder.getBytesPerSec();
    pcmLen = decoder.getPCMLen();
}

void ni::utils::Sample::loadMp3(std::string_view path)
{
    // TODO
    ni::core::utilsLogger->critical("mp3 audio is not supported yet");
	std::terminate();
}

void ni::utils::Sample::loadOgg(std::string_view path)
{
    // TODO
    ni::core::utilsLogger->critical("ogg audio is not supported yet");
	std::terminate();
}
