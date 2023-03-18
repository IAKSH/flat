#include <chrono>
#include <thread>
#include <iostream>
#include <gtest/gtest.h>

#include "alsoft_imp.hpp"

TEST(RendererTest, PlayMp3)
{
    audapi::AudioMixer<alsoft::AudioMixer>&& mixer = alsoft::AudioMixer();
    auto source = mixer.genAudioSource();
    auto mp3 = mixer.genAudio("../../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
    //source->setAttrib(std::move(audapi::AudioAttrib(audapi::AudioAttribType::gain,1.0f)));
    source->setAttrib(audapi::AudioAttrib(audapi::AudioAttribType::gain,1.0f));

    mixer << audapi::AudioAttrib(audapi::AudioAttribType::gain,0.2f) << (*source)(*mp3);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}