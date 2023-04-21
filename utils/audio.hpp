#pragma once

#include "../core/template.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>

namespace ni::utils
{
	class Audio : public core::DisableCopy
	{
	protected:
		ALuint bufferID;
		virtual void loadWavFromFile(std::string_view path);
		virtual void loadMp3FromFile(std::string_view path);
		virtual void loadOggFromFile(std::string_view path);
		virtual void loadFlacFromFile(std::string_view path);

	public:
		Audio();
		Audio(std::string_view path);
		~Audio();
		const ALuint& getBufferID() const { return bufferID; }
		void loadFromFile(std::string_view path);
	};

	class SoundEffect : public Audio
	{
	private:
		virtual void loadWavFromFile(std::string_view path) override;
		virtual void loadMp3FromFile(std::string_view path) override;
		virtual void loadOggFromFile(std::string_view path) override;
		virtual void loadFlacFromFile(std::string_view path) override;

	public:
		SoundEffect() : Audio() {}
		SoundEffect(std::string_view path) : Audio(path) {}
		~SoundEffect() = default;
	};
}