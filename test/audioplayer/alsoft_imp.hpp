#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

#include "abstruct_api.hpp"

namespace alsoft
{
    class Audio : public audapi::Audio
    {
    private:
        uint32_t bufferId;
        void releaseAudio();
        void checkBuffer();

    public:
        Audio(uint32_t id) : bufferId(id) {}
        virtual ~Audio() override { alDeleteBuffers(1, &bufferId); }
        uint32_t getAudioId() { return bufferId; }
    };

    class AudioSource : public audapi::AudioSource
    {
    private:
        uint32_t sourceId;
        int offset;

    public:
        AudioSource(uint32_t id) : sourceId(id) {}
        ~AudioSource() { alDeleteSources(1, &sourceId); }

        uint32_t getSourceid() { return sourceId; }

        int getOffset() { return offset; }
        void setOffset(int i) { offset = i; }

        virtual std::function<void(float)> operator[](audapi::AudioAttribType type) override
        {
            auto func = [&type,this](float f) {
                uint32_t id = this->sourceId;
                float oriPos[3];
                float oriVel[3];
                alGetSource3f(id, AL_POSITION, oriPos, oriPos + 1, oriPos + 2);
                alGetSource3f(id, AL_VELOCITY, oriVel, oriVel + 1, oriVel + 2);

                switch(type)
                {
                case audapi::AudioAttribType::positionX:
                    alSource3f(id, AL_POSITION, f, oriPos[1], oriPos[2]);
                    break;
                case audapi::AudioAttribType::positionY:
                    alSource3f(id, AL_POSITION, oriPos[0], f, oriPos[2]);
                    break;
                case audapi::AudioAttribType::positionZ:
                    alSource3f(id, AL_POSITION, oriPos[0], oriPos[1], f);
                    break;
                case audapi::AudioAttribType::velocityX:
                    alSource3f(id, AL_VELOCITY, f, oriVel[1], oriVel[2]);
                    break;
                case audapi::AudioAttribType::velocityY:
                    alSource3f(id, AL_VELOCITY, oriVel[0], f, oriVel[2]);
                    break;
                case audapi::AudioAttribType::velocityZ:
                    alSource3f(id, AL_VELOCITY, oriVel[0], oriVel[1], f);
                    break;
                case audapi::AudioAttribType::looping:
                    alSourcei(id, AL_LOOPING, static_cast<ALboolean>(f));
                    break;
                case audapi::AudioAttribType::gain:
                    alSourcef(id, AL_GAIN, f);
                    break;
                default:
                    std::cerr << "error: wrong attrib for audio source" << std::endl;
                    abort();
                }
            };

            return func;
        }
    };

    class AudioMixer : public audapi::AudioMixer<AudioMixer>
    {
    private:
        ALCdevice* device;
        ALCcontext* context;

    public:
        AudioMixer()
        {
            device = alcOpenDevice(nullptr);
            context = alcCreateContext(device, nullptr);
            alcMakeContextCurrent(context);

            ALenum error = alGetError();
            if(error != AL_NO_ERROR)
                std::cerr << "OpenAL error: " << alGetString(error) << std::endl;
        }

        ~AudioMixer()
        {
            alcDestroyContext(context);
            alcCloseDevice(device);
        }

        void imp_playAudioFromSource(audapi::AudioSource& _source)
        {
            if(typeid(_source) != typeid(AudioSource))
            {
                std::cerr << "wrong audio source type" << std::endl;
                abort();
            }

            AudioSource& source = (AudioSource&)_source;

            if(typeid(source.getCurrentAudio()) != typeid(Audio))
            {
                std::cerr << "wrong audio type" << std::endl;
                abort();
            }

            Audio& audio = (Audio&)source.getCurrentAudio();

            alSourcei(source.getSourceid(), AL_BUFFER, audio.getAudioId());
            alSourcePlay(source.getSourceid());
        }

        void imp_setAttrib(audapi::AudioAttrib& attrib)
        {
            float oriPos[3];
            float oriVel[3];
            alGetListener3f(AL_POSITION, oriPos, oriPos + 1, oriPos + 2);
            alGetListener3f(AL_VELOCITY, oriVel, oriVel + 1, oriVel + 2);

            switch(attrib.getType())
            {
            case audapi::AudioAttribType::positionX:
                alListener3f(AL_POSITION, attrib.getVal(), oriPos[1], oriPos[2]);
                break;
            case audapi::AudioAttribType::positionY:
                alListener3f(AL_POSITION, oriPos[0], attrib.getVal(), oriPos[2]);
                break;
            case audapi::AudioAttribType::positionZ:
                alListener3f(AL_POSITION, oriPos[0], oriPos[1], attrib.getVal());
                break;
            case audapi::AudioAttribType::velocityX:
                alListener3f(AL_VELOCITY, attrib.getVal(), oriVel[1], oriVel[2]);
                break;
            case audapi::AudioAttribType::velocityY:
                alListener3f(AL_VELOCITY, oriVel[0], attrib.getVal(), oriVel[2]);
                break;
            case audapi::AudioAttribType::velocityZ:
                alListener3f(AL_VELOCITY, oriVel[0], oriVel[1], attrib.getVal());
                break;
            case audapi::AudioAttribType::looping:
                alListeneri(AL_LOOPING, static_cast<ALboolean>(attrib.getVal()));
                break;
            case audapi::AudioAttribType::gain:
                alListeneri(AL_GAIN, attrib.getVal());
                break;
            }
        }

        std::unique_ptr<audapi::AudioSource> imp_genAudioSource()
        {
            uint32_t sourceId;
            alGenSources(1, &sourceId);
            return std::make_unique<AudioSource>(sourceId);
        }

        std::unique_ptr<Audio> imp_genAudio(std::string_view path)
        {
            // read in the whole mp3 file
            std::ifstream ifs(path.data(), std::ios::binary);
            if(!ifs)
            {
                std::cerr << "[ERROR] Can't open " << path << std::endl;
                abort();
            }
            ifs.seekg(0, std::ios::end);
            std::streampos fileSize = ifs.tellg();
            ifs.seekg(0, std::ios::beg);
            // std::vector<uint8_t> mp3Binary(fileSize);
            std::unique_ptr<uint8_t[]> mp3Binary = std::make_unique<uint8_t[]>(static_cast<long>(fileSize));
            ifs.read((char*)(mp3Binary.get()), fileSize);
            ifs.close();

            // decode with minimp3
            mp3dec_t mp3d;
            mp3dec_frame_info_t info;
            std::vector<short> allPCM;
            short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
            int readLength = 0;
            // decode frame by frame
            int samples = mp3dec_decode_frame(&mp3d, mp3Binary.get(), static_cast<int>(fileSize), pcm, &info);
            while(samples)
            {
                // collect pcm
                for(auto item : pcm)
                    allPCM.push_back(item);
                readLength += info.frame_bytes;
                samples = mp3dec_decode_frame(&mp3d, mp3Binary.get() + readLength, static_cast<int>(fileSize) - readLength, pcm, &info);
            }

            // prepare OpenAL buffer
            uint32_t bufferId;
            alGenBuffers(1, &bufferId);
            ALenum format = (info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
            alBufferData(bufferId, format, allPCM.data(), allPCM.size() * sizeof(short), info.hz);
            return std::make_unique<Audio>(bufferId);
        }

        void imp_stopAudioSource(audapi::StopFlag& flag)
        {
            if(typeid(flag.getAudioSource()) != typeid(AudioSource))
            {
                std::cerr << "error: wrong audio source type in stop flag" << std::endl;
                abort();
            }

            AudioSource& source = (AudioSource&)flag.getAudioSource();
            int offset;
            alSourcePause(source.getSourceid());
            alGetSourcei(source.getSourceid(), AL_SAMPLE_OFFSET, &offset);
            source.setOffset(offset);
        }

        void imp_resumeAudioSource(audapi::ResumeFlag& flag)
        {
            if(typeid(flag.getAudioSource()) != typeid(AudioSource))
            {
                std::cerr << "error: wrong audio source type in resume flag" << std::endl;
                abort();
            }

            AudioSource& source = (AudioSource&)flag.getAudioSource();
            alSourcePlay(source.getSourceid());
            alSourcei(source.getSourceid(), AL_SAMPLE_OFFSET, source.getOffset());
        }
    };
}  // namespace alsoft