#include "wav_dec.hpp"
#include "logger.hpp"
#include <exception>
#include <memory>
#include <vector>

ni::utils::WavDecoder::WavDecoder(std::string_view path)
{
    ifs.open(path,std::ios::in | std::ios::binary);
    if(!ifs)
    {
        ni::utils::coreLogger()->critical("failed to open file at {}",path);
        std::terminate();
    }

    load();
}

void ni::utils::WavDecoder::load()
{
    ifs.read(reinterpret_cast<char*>(&structure), sizeof(structure));
    if (std::string(structure.chunkID, 4) != "RIFF" ||
        std::string(structure.format, 4) != "WAVE" ||
        std::string(structure.subchunk1ID, 4) != "fmt ")
    {
        ni::utils::coreLogger()->critical("trying to decode a non-wav file");
        std::terminate();
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

    ni::utils::coreLogger()->critical("can't locate data chunk in WAV file");
    std::terminate();
}