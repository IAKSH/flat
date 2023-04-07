#pragma once

#include <string>

#include <al/al.h>
#include <al/alc.h>

namespace ni::utils
{
	class Audio
	{
	private:
		 ALuint bufferID;

	public:
		Audio();
		Audio(std::string_view path);
		~Audio();
		const ALuint& getBufferID() { return bufferID; }
		void loadFromFile(std::string_view path);
	};
}