#pragma once

#include <string>

#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils
{
	class Audio
	{
	private:
		 ALuint bufferID;

	public:
		Audio();
		Audio(Audio&) = delete;
		Audio(std::string_view path);
		~Audio();
		const ALuint& getBufferID() const { return bufferID; }
		void loadFromFile(std::string_view path);
	};
}