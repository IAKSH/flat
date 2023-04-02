#pragma once

#include <string_view>

#include <al/al.h>
#include <al/alc.h>

namespace flat::utils
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