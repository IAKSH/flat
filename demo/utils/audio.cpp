#include "audio.hpp"

#include <fstream>

#include "log.hpp"

#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

flat::utils::Audio::Audio()
	: bufferID(0)
{

}

flat::utils::Audio::Audio(std::string_view path)
	: Audio()
{
	loadFromFile(path);
}

flat::utils::Audio::~Audio()
{
	if (bufferID)
	{
		LOG_TRACE("deleted audio buffer with id = {}", bufferID);
		alDeleteBuffers(1, &bufferID);
	}
}

void flat::utils::Audio::loadFromFile(std::string_view path)
{
	LOG_TRACE("loading audio from {}", path.data());

	// read in the whole mp3 file
	std::ifstream ifs(path.data(), std::ios::binary);
	if (!ifs)
	{
		LOG_CRITICAL("can't open audio file at {}", path.data());
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
	while (samples)
	{
		// collect pcm
		for (auto item : pcm)
			allPCM.push_back(item);
		readLength += info.frame_bytes;
		samples = mp3dec_decode_frame(&mp3d, mp3Binary.get() + readLength, static_cast<int>(fileSize) - readLength, pcm, &info);
	}

	// prepare OpenAL buffer
	alGenBuffers(1, &bufferID);
	ALenum format = (info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
	alBufferData(bufferID, format, allPCM.data(), allPCM.size() * sizeof(short), info.hz);

	LOG_TRACE("OK");
}