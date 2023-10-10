#include <AL/al.h>
#include <AL/alc.h>
#include <thread>
#include <iostream>
#include <quick_al/device.hpp>
#include <quick_al/context.hpp>
#include <quick_al/buffer.hpp>
#include <quick_al/source.hpp>
#include <quick_al/sample.hpp>

static constexpr std::string_view BGM_PATH = "D:/Programming-Playground/wav_audio/heart.wav";
static quick3d::al::Sample sample(BGM_PATH);

void directly_oal_api() noexcept
{
	ALCdevice* device = alcOpenDevice(nullptr);
	ALCcontext* context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context))
		std::cerr << "can't make alc context current" << std::endl;

	ALuint source_id;
	alGenSources(1, &source_id);

	ALuint buffer_id;
	alGenBuffers(1, &buffer_id);

	alBufferData(buffer_id, AL_FORMAT_MONO16,
		sample.get_codec().get_sample_pcm(),
		sample.get_codec().get_sample_size(),
		sample.get_codec().get_sample_freq());

	alSourcei(source_id, AL_LOOPING, AL_TRUE);
	alSourcei(source_id, AL_BUFFER, buffer_id);
	alSourcePlay(source_id);

	while (true)
		std::this_thread::sleep_for(std::chrono::seconds(1));
}

void quick_al_api()
{
	using namespace quick3d::al;
	
	Device device(nullptr);
	Context context(device);


	Buffer buffer(
		sample.get_codec().get_sample_channels(),
		sample.get_codec().get_sample_bps(),
		sample.get_codec().get_sample_pcm(),
		sample.get_codec().get_sample_size(),
		sample.get_codec().get_sample_freq());

	Source source(buffer);
	source.set_source_looping(true);
	source.play_sound();

	while (true)
		std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() noexcept
{
	quick_al_api();
}