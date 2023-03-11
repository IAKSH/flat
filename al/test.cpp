#include <iostream>

#include "al_audio.hpp"

int main()
{
    flat::al::Listener _listener;
    flat::al::Source _source;
    flat::AudioListener& listener = _listener;
    flat::AudioSource& source = _source;

    listener.initAudioListner();
    source.initAudioSource();
    source.setAudioSourceLooping(true);

    std::cout << "f*cking C++\n" << listener.getAudioListenerGain() << std::endl;
    return 0;
}