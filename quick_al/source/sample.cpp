#include <format>
#include <fstream>
#include <stdexcept>
#include <quick_al/sample.hpp>

quick3d::al::Wavcodec::Wavcodec(std::ifstream& ifs) noexcept(false)
{
    load_from_ifs(ifs);
}

void quick3d::al::Wavcodec::load_from_ifs(std::ifstream& ifs) noexcept(false)
{
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];
    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char subchunk2_id[4];
    uint32_t subchunk2_size;

    ifs.seekg(0, std::ios::beg);
    ifs.read(chunk_id, 4);
    ifs.read(reinterpret_cast<char*>(&chunk_size), 4);
    ifs.read(format, 4);
    ifs.read(subchunk1_id, 4);
    ifs.read(reinterpret_cast<char*>(&subchunk1_size), 4);
    ifs.read(reinterpret_cast<char*>(&audio_format), 2);
    ifs.read(reinterpret_cast<char*>(&num_channels), 2);
    ifs.read(reinterpret_cast<char*>(&sample_rate), 4);
    ifs.read(reinterpret_cast<char*>(&byte_rate), 4);
    ifs.read(reinterpret_cast<char*>(&block_align), 2);
    ifs.read(reinterpret_cast<char*>(&bits_per_sample), 2);
    ifs.read(subchunk2_id, 4);
    ifs.read(reinterpret_cast<char*>(&subchunk2_size), 4);

    if (std::string_view(chunk_id, 4) != "RIFF" ||
        std::string_view(format, 4) != "WAVE" ||
        std::string_view(subchunk1_id, 4) != "fmt " ||
        audio_format != 1 ||
        std::string_view(subchunk2_id, 4) != "data")
    {
        throw std::runtime_error("invalid WAV audio file format");
    }

    channels = num_channels;
    bps = bits_per_sample;
    size = subchunk2_size;
    freq = sample_rate;

    pcm = std::make_unique<unsigned char[]>(size);
    ifs.read(reinterpret_cast<char*>(pcm.get()), size);
}

unsigned char* quick3d::al::Wavcodec::Wavcodec::get_sample_pcm() const noexcept
{
    return pcm.get();
}

uint16_t quick3d::al::Wavcodec::Wavcodec::get_sample_channels() const noexcept
{
    return channels;
}

uint16_t quick3d::al::Wavcodec::Wavcodec::get_sample_bps() const noexcept
{
    return bps;
}

uint32_t quick3d::al::Wavcodec::Wavcodec::get_sample_size() const noexcept
{
    return size;
}

uint32_t quick3d::al::Wavcodec::Wavcodec::get_sample_freq() const noexcept
{
    return freq;
}

bool quick3d::al::Sample::is_wav_audio(std::istream& ifs) noexcept
{
    char header[12];
    ifs.read(header, 12);

    return std::string_view(header, 4) == "RIFF" &&
        std::string_view(header + 8, 4) == "WAVE";
}

quick3d::al::Sample::Sample(std::string_view path) noexcept(false)
{
    std::ifstream file(path.data(), std::ios::binary);
    if (!file)
        throw std::runtime_error(std::format("failed to open audio file from {}", path));

    if (is_wav_audio(file))
        codec = new Wavcodec(file);
    else
        throw std::runtime_error("unsupported audio file format");

    file.close();
}

quick3d::al::Sample::~Sample() noexcept
{
    delete codec;
}

const quick3d::al::PCMcodec& quick3d::al::Sample::get_codec() const noexcept
{
    return *codec;
}