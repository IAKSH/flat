#include "al_audio.hpp"

#include <vector>
#include <fstream>

#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

flat::Mp3Audio::Mp3Audio()
    : alBufferId(0)
{
}

flat::Mp3Audio::~Mp3Audio()
{
}

void flat::Mp3Audio::loadAudioFromFile(std::filesystem::path path)
{
    // old trash code
    // read in the whole mp3 file
    std::ifstream ifs(path.c_str(), std::ios::binary);
    if (!ifs)
    {
        std::cerr << "[ERROR] Can't open " << path << std::endl;
        abort();
    }
    ifs.seekg(0, std::ios::end);
    std::streampos fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<uint8_t> mp3Binary(fileSize);
    ifs.read((char *)(mp3Binary.data()), fileSize);
    ifs.close();

    // decode with minimp3
    mp3dec_t mp3d;
    mp3dec_frame_info_t info;
    std::vector<short> allPCM;
    short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
    int readLength = 0;
    // decode frame by frame
    int samples = mp3dec_decode_frame(&mp3d, mp3Binary.data(), static_cast<int>(fileSize), pcm, &info);
    while (samples)
    {
        // collect pcm
        for (auto item : pcm)
            allPCM.push_back(item);
        readLength += info.frame_bytes;
        samples = mp3dec_decode_frame(&mp3d, mp3Binary.data() + readLength, static_cast<int>(fileSize) - readLength, pcm, &info);
    }

    // prepare OpenAL buffer
    alGenBuffers(1, &alBufferId);
    ALenum format = (info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
    alBufferData(alBufferId, format, allPCM.data(), allPCM.size() * sizeof(short), info.hz);
}

void flat::Mp3Audio::releaseAudio()
{
    alDeleteBuffers(1,&alBufferId);
}

uint32_t const flat::Mp3Audio::getAudioBufferId()
{
    return alBufferId;
}

flat::WavAudio::WavAudio()
    : alBufferId(0)
{
}

flat::WavAudio::~WavAudio()
{
}

void flat::WavAudio::loadAudioFromFile(std::filesystem::path path)
{
    // super bad code for test only
    wava::WavAudio wav(path.string().c_str());
    alBufferId = wav.getBuffer();
}

void flat::WavAudio::releaseAudio()
{
    alDeleteBuffers(1,&alBufferId);
}

uint32_t const flat::WavAudio::getAudioBufferId()
{
    return alBufferId;
}

flat::ALAudioSource::ALAudioSource()
    : alSourceId(0)
{
}

flat::ALAudioSource::~ALAudioSource()
{
}

void flat::ALAudioSource::initAudioSource()
{
    alGenSources(1, &alSourceId);
    alSourcef(alSourceId, AL_PITCH, 1.0f);
    alSourcef(alSourceId, AL_GAIN, 0.25f);
    alSource3f(alSourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(alSourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(alSourceId, AL_LOOPING, false);
}

void flat::ALAudioSource::releaseAudioSource()
{
    alDeleteSources(1,&alSourceId);
}

void flat::ALAudioSource::pauseAudio()
{
    alSourcePause(alSourceId);
    alGetSourcei(alSourceId, AL_SAMPLE_OFFSET, &alSampleOffset);
}

void flat::ALAudioSource::resumeAudio()
{
    alSourcePlay(alSourceId);
    alSourcei(alSourceId, AL_SAMPLE_OFFSET, alSampleOffset);
}

void flat::ALAudioSource::playAudio(uint32_t bufferId)
{
    alSourcei(alSourceId, AL_BUFFER, bufferId);
    alSourcePlay(alSourceId);
}

void flat::ALAudioSource::setAudioSourcePosition(float x,float y,float z)
{
    alSource3f(alSourceId, AL_POSITION,x,y,z);
}

void flat::ALAudioSource::setAudioSourceVelocity(float x,float y,float z)
{
    alSource3f(alSourceId, AL_POSITION,x,y,z);
}

void flat::ALAudioSource::addAudioSourcePosition(float x,float y,float z)
{
    float oriX = getAudioSourcePosX() + x;
    float oriY = getAudioSourcePosY() + y;
    float oriZ = getAudioSourcePosZ() + z;
    alSource3f(alSourceId,AL_POSITION,oriX,oriY,oriZ);
}

void flat::ALAudioSource::addAudioSourceVelocity(float x,float y,float z)
{
    float oriX = getAudioSourceVelX() + x;
    float oriY = getAudioSourceVelY() + y;
    float oriZ = getAudioSourceVelZ() + z;
    alSource3f(alSourceId,AL_VELOCITY,oriX,oriY,oriZ);
}

void flat::ALAudioSource::setAudioSourceVolume(float v)
{
    alSourcef(alSourceId,AL_GAIN,v);
}

void flat::ALAudioSource::setAudioSourceLooping(bool b)
{
    alSourcei(alSourceId,AL_LOOPING,b);
}

bool const flat::ALAudioSource::getAudioSourceLooping()
{
    bool buffer;
    alGetSourcei(alSourceId,AL_LOOPING,(ALint*)(&buffer));
    return buffer;
}

float const flat::ALAudioSource::getAudioSourcePosX()
{
    float buffer;
    alGetSource3f(alSourceId,AL_POSITION,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourcePosY()
{
    float buffer;
    alGetSource3f(alSourceId,AL_POSITION,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourcePosZ()
{
    float buffer;
    alGetSource3f(alSourceId,AL_POSITION,nullptr,nullptr,&buffer);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourceVelX()
{
    float buffer;
    alGetSource3f(alSourceId,AL_VELOCITY,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourceVelY()
{
    float buffer;
    alGetSource3f(alSourceId,AL_VELOCITY,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourceVelZ()
{
    float buffer;
    alGetSource3f(alSourceId,AL_VELOCITY,nullptr,nullptr,&buffer);
    return buffer;
}

float const flat::ALAudioSource::getAudioSourceVolume()
{
    float buffer;
    alGetSourcef(alSourceId,AL_GAIN,&buffer);
    return buffer;
}

flat::ALAudioListener::ALAudioListener()
{
}

flat::ALAudioListener::~ALAudioListener()
{
}

void flat::ALAudioListener::initAudioListener()
{
    device = alcOpenDevice(NULL);
    if (!device)
    {
        std::cout << "OpenAL Error | Can't open OpenAL device" << std::endl;
        abort();
    }

    context = alcCreateContext(device, NULL);
    if (!context)
    {
        std::cout << "OpenAL Error | Can't create OpenAL context" << std::endl;
        // alcCloseDevice(device);
        abort();
    }

    alcMakeContextCurrent(context);
}

void flat::ALAudioListener::releaseAudioListener()
{
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void flat::ALAudioListener::setAudioListenerPosition(float x,float y,float z)
{
    alListener3f(AL_POSITION,x,y,z);
}

void flat::ALAudioListener::setAudioListenerVelocity(float x,float y,float z)
{
    alListener3f(AL_VELOCITY,x,y,z);
}

void flat::ALAudioListener::addAudioListenerPosition(float x,float y,float z)
{
    float oriX = getAudioListenerPosX() + x;
    float oriY = getAudioListenerPosY() + y;
    float oriZ = getAudioListenerPosZ() + z;
    alListener3f(AL_POSITION,oriX,oriY,oriZ);
}

void flat::ALAudioListener::addAudioListenerVelocity(float x,float y,float z)
{
    float oriX = getAudioListenerVelX() + x;
    float oriY = getAudioListenerVelY() + y;
    float oriZ = getAudioListenerVelZ() + z;
    alListener3f(AL_VELOCITY,oriX,oriY,oriZ);
}

void flat::ALAudioListener::setAudioListenerVolume(float v)
{
    alListenerf(AL_GAIN,v);
}

float const flat::ALAudioListener::getAudioListenerPosX()
{
    float buffer;
    alGetListener3f(AL_POSITION,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerPosY()
{
    float buffer;
    alGetListener3f(AL_POSITION,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerPosZ()
{
    float buffer;
    alGetListener3f(AL_POSITION,nullptr,nullptr,&buffer);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerVelX()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerVelY()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerVelZ()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,nullptr,nullptr,&buffer);
    return buffer;
}

float const flat::ALAudioListener::getAudioListenerVolume()
{
    float buffer;
    alGetListenerf(AL_GAIN,&buffer);
    return buffer;
}
