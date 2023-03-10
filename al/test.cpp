#include <iostream>

#include "al_audio.hpp"

int main()
{
    flat::ALAudioListener alListener;
    flat::ALAudioSource alSource1,alSource2;
    flat::Mp3Audio mp3;
    flat::WavAudio wav;

    flat::Audio& audio1 = mp3;
    flat::Audio& audio2 = wav;
    flat::AudioListener& listner = alListener;
    flat::AudioSource& source1 = alSource1;
    flat::AudioSource& source2 = alSource2;

    audio1.loadAudioFromFile("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
    audio2.loadAudioFromFile("../../demo/sounds/test_sounds_walk.wav");

    listner.initAudioListener();
    listner.setAudioListenerVolume(0.5f);

    source1.initAudioSource();
    source1.setAudioSourceLooping(false);
    source1.setAudioSourceVelocity(0.001f,0.0f,0.0f);

    source2.initAudioSource();
    source2.setAudioSourceLooping(true);

    source1.playAudio(audio1.getAudioBufferId());
    source2.playAudio(audio2.getAudioBufferId());

    while(true)
    {
        source1.addAudioSourcePosition(0.001f,0.0f,0.0f);
    }

    return 0;
}