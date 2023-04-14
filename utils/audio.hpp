#pragma once

#include <string>

#include <AL/al.h>
#include <AL/alc.h>
#include <string_view>

namespace ni::utils
{
	class Audio
	{
	private:
		ALuint bufferID;
		void loadWavFromFile(std::string_view path);
		void loadMp3FromFile(std::string_view path);
		void loadOggFromFile(std::string_view path);
		void loadFlacFromFile(std::string_view path);

	public:
		Audio();
		Audio(Audio&) = delete;
		Audio(std::string_view path);
		~Audio();
		const ALuint& getBufferID() const { return bufferID; }
		void loadFromFile(std::string_view path);
	};
}