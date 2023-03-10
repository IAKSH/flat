#include "wavaudio.hpp"

int wava::WavAudio::getFileCursorMark(std::ifstream &fs, std::string mark)
{
    int len = mark.length();
    // dynamic C-style array may not work on msvc
    // if that happens, fix it by yourself
    // it's sample, good luck
    char* buf = new char[len + 1];
    buf[len] = '\0';
    int i = 0;
    while (!fs.eof())
    {
        fs.seekg(i++, std::ios::beg);
        fs.read(buf, sizeof(char) * len);
        if (mark.compare(buf) == 0)
        {
            delete[] buf;
            return i;
        }
    }
    std::cerr << "[libwavaudio] ERROR: failed to locate mark (" << mark << ") in moveFileCursorToMark()\n";
    abort();
}

wava::WavAudio::WavAudio()
{
}

wava::WavAudio::WavAudio(const char *path)
{
    load(path);
}

wava::WavAudio::~WavAudio()
{
    //alDeleteBuffers(1, &buffer);
}

void wava::WavAudio::load(const char *path)
{
    int i;
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    if(!fs)
    {
        std::cerr << "[libwavaudio] ERROR: can't open file (" << path << ")\n";
        abort(); 
    }
    
    i = getFileCursorMark(fs, "RIFF") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char *)&chunkSize, 4);
    fs.seekg(i + 8, std::ios::beg);
    fs.read((char *)&format, 4);

    if (std::string(format).compare("WAVE") != 0)
    {
        std::cerr << "[libwavaudio] ERROR: trying to load a none-wav format file (" << path << ")\n";
        abort();
    }

    i = getFileCursorMark(fs, "fmt") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char *)&subChunk1Size, 4);
    fs.seekg(i + 8, std::ios::beg);
    fs.read((char *)&audioFormat, 2);
    fs.seekg(i + 10, std::ios::beg);
    fs.read((char *)&numChannels, 2);
    fs.seekg(i + 12, std::ios::beg);
    fs.read((char *)&sampleRate, 4);
    fs.seekg(i + 16, std::ios::beg);
    fs.read((char *)&byteRate, 4);
    fs.seekg(i + 20, std::ios::beg);
    fs.read((char *)&blockAlign, 2);
    fs.seekg(i + 22, std::ios::beg);
    fs.read((char *)&bitsPerSample, 2);
    fs.seekg(i + 24, std::ios::beg);

    i = getFileCursorMark(fs, "data") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char *)&subChunk2Size, 4);
    fs.seekg(i + 8, std::ios::beg);
    data = new unsigned char[subChunk2Size];
    fs.read((char *)data, subChunk2Size);

    // load data to OpenAL buffer
    alGenBuffers(1, &buffer);
    if (bitsPerSample == 16)
    {
        if (numChannels == 1)
            alBufferData(buffer, AL_FORMAT_MONO16, data, subChunk2Size, sampleRate);
        else if (numChannels == 2)
            alBufferData(buffer, AL_FORMAT_STEREO16, data, subChunk2Size, sampleRate);
        else
            abort();
    }
    else if (bitsPerSample == 8)
    {
        if (numChannels == 1)
            alBufferData(buffer, AL_FORMAT_MONO8, data, subChunk2Size, sampleRate);
        else if (numChannels == 2)
            alBufferData(buffer, AL_FORMAT_STEREO8, data, subChunk2Size, sampleRate);
        else
            abort();
    }
    else
        abort();

    // release data
    delete[] data;
    fs.close();

    loaded = true;
}

uint32_t wava::WavAudio::getBuffer()
{
    if (loaded)
        return buffer;
    else
    {
        std::cerr << "[libwavaudio] ERROR: called getBuffer() from an unloaded WavAudio\n";
        abort();
    }
}