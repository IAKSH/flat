#include <thread>
#include <chrono>
#include <iostream>

#include "al_audio.hpp"

int main()
{
    flat::al::Listener _listener;
    flat::al::Source _source;
    //flat::al::Audio _audio;
    flat::AudioListener& listener = _listener;
    flat::AudioSource& source = _source;
    //flat::Audio& audio = _audio;

    //audio.loadAudioFromFile("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

    listener.initAudioListner();
    source.initAudioSource();
    source.setAudioSourceLooping(true);
    //source.playAudio(audio.getAudioId());

    std::cout << "f*cking C++\n" << listener.getAudioListenerGain() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}