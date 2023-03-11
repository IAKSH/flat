#include <thread>
#include <chrono>
#include <iostream>

#include "al_audio.hpp"

void checkError()
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
        std::cerr << "OpenAL error: " << alGetString(error) << std::endl;
}

int main()
{
    flat::al::Listener _listener;
    flat::al::Source _source;
    flat::al::Audio _audio;
    flat::AudioListener& listener = _listener;
    flat::AudioSource& source = _source;
    flat::Audio& audio = _audio;

    listener.initAudioListner();
    audio.loadAudioFromFile("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

    checkError();

    listener.setAudioListenerGain(1.0f);

    checkError();

    listener.setAudioListenerPosition(0.0f,0.0f,0.0f);

    checkError();

    listener.setAudioListenerVelocity(0.0f,0.0f,0.0f);

    checkError();

    source.initAudioSource();

    checkError();

    source.setAudioSourceGain(1.0f);

    checkError();

    source.setAudioSourcePosition(0.0f,0.0f,0.0f);

    checkError();

    source.setAudioSourceVelocity(0.0f,0.0f,0.0f);

    checkError();

    source.setAudioSourceLooping(true);

    checkError();

    source.playAudio(audio.getAudioId());

    checkError();

    std::cout << "f*cking C++\n" << listener.getAudioListenerGain() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}