#include <thread>
#include <chrono>
#include <iostream>

#include "flat_al/audio.hpp"

void checkError()
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
        std::cerr << "OpenAL error: " << alGetString(error) << std::endl;
}

int main()
{
    flat::al::Listener _listener;
    flat::al::Source _source0;
    flat::al::Source _source1;
    flat::al::Audio _audio0;
    flat::al::Audio _audio1;
    flat::AudioListener& listener = _listener;
    flat::AudioSource& mp3Source = _source0;
    flat::AudioSource& wavSource = _source1;
    flat::Audio& mp3Audio = _audio0;
    flat::Audio& wavAudio = _audio1;

    listener.initAudioListner();
    mp3Audio.loadAudioFromFile("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
    wavAudio.loadAudioFromFile("../../demo/sounds/test_sounds_walk.wav");

    checkError();

    listener.setAudioListenerGain(1.0f);

    checkError();

    listener.setAudioListenerPosition(0.0f,0.0f,0.0f);

    checkError();

    listener.setAudioListenerVelocity(0.0f,0.0f,0.0f);

    checkError();

    mp3Source.initAudioSource();
    wavSource.initAudioSource();

    checkError();

    mp3Source.setAudioSourceGain(0.25f);
    wavSource.setAudioSourceGain(1.0f);

    checkError();

    mp3Source.setAudioSourcePosition(0.0f,0.0f,0.0f);
    wavSource.setAudioSourcePosition(1.0f,0.0f,0.0f);

    checkError();

    mp3Source.setAudioSourceVelocity(0.0f,0.0f,0.0f);
    wavSource.setAudioSourceVelocity(-0.5f,0.0f,0.0f);

    checkError();

    mp3Source.setAudioSourceLooping(true);
    wavSource.setAudioSourceLooping(true);

    checkError();

    mp3Source.playAudio(mp3Audio.getAudioId());
    wavSource.playAudio(wavAudio.getAudioId());

    checkError();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}