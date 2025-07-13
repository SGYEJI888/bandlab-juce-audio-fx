#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider gainSlider;

    // 📌 여기 아래 추가!
    juce::AudioBuffer<float> delayBuffer;
    int writePosition = 0;
    int readPosition = 0;

    bool useDelay = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
