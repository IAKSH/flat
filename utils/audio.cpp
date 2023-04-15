#include "audio.hpp"

#include <fstream>
#include <filesystem>
#include <memory>
#include <string_view>

#include "AL/al.h"
#include "logger.hpp"
#include "wav_dec.hpp"

ni::utils::Audio::Audio()
	: bufferID(0)
{

}

ni::utils::Audio::Audio(std::string_view path)
	: Audio()
{
	loadFromFile(path);
}

ni::utils::Audio::~Audio()
{
	if (bufferID)
	{
		utils::coreLogger()->trace("deleting audio buffer with id = {}", bufferID);
		alDeleteBuffers(1, &bufferID);
	}
}

void ni::utils::Audio::loadFromFile(std::string_view path)
{
    std::filesystem::path file_path(path);
    std::string extension = file_path.extension().string();
	if(extension == std::string_view{".mp3"})
		loadMp3FromFile(path);
	else if(extension == std::string_view{".wav"})
		loadWavFromFile(path);
	else if(extension == std::string_view{".ogg"})
		loadOggFromFile(path);
	else if(extension == std::string_view{".flac"})
		loadFlacFromFile(path);
	else
	{
		ni::utils::coreLogger()->critical("unknow extension type: {} ({})",extension,path);
		abort();
	}
}

void ni::utils::Audio::loadMp3FromFile(std::string_view path)
{
	// TODO
	ni::utils::coreLogger()->critical("mp3 audio is not supported yet");
	abort();
}

void ni::utils::Audio::loadWavFromFile(std::string_view path)
{
    AudioDecoder<WavDecoder>&& decoder = WavDecoder(path);
    ALenum format;

    if (decoder.getBytesPerSec() == 16)
        format = (decoder.getChannelCount() == 1 ? AL_FORMAT_MONO16:AL_FORMAT_STEREO16);
    else if (decoder.getBytesPerSec() == 8)
        format = (decoder.getChannelCount() == 1 ? AL_FORMAT_MONO8:AL_FORMAT_STEREO8);
    else
    {
        ni::utils::coreLogger()->critical("unsupported bytes per second ({} bits), WAV decoder only handles 8- and 16-bit", decoder.getBytesPerSec());
        abort();
    }

    alGenBuffers(1, &bufferID);
    alBufferData(bufferID,format,decoder.getPCM(),decoder.getPCMLength(), decoder.getSimpleRate());
}

void ni::utils::Audio::loadOggFromFile(std::string_view path)
{
	// TODO
	ni::utils::coreLogger()->critical("ogg audio is not supported yet");
	abort();
}

void ni::utils::Audio::loadFlacFromFile(std::string_view path)
{
	// TODO
	ni::utils::coreLogger()->critical("flac audio is not supported yet");
	abort();
}
