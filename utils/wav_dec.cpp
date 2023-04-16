#include "wav_dec.hpp"
#include "logger.hpp"
#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

ni::utils::WavDecoder::WavDecoder(std::string_view path)
{
    try
    {
        load(path);
        return;
    }
    catch(const std::exception& e)
    {
        ni::utils::coreLogger()->critical("exception catched in WavDecoder: {}",e.what());
    }
    std::terminate();
}

void ni::utils::WavDecoder::load(std::string_view path) noexcept(false)
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