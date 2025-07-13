#include "MainComponent.h"
#include <juce_audio_basics/juce_audio_basics.h>

//==============================================================================
MainComponent::MainComponent()
{
    setSize(600, 400);

    // 슬라이더 기본 설정
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    addAndMakeVisible(gainSlider);

    // 오디오 채널: 입력 2 (스테레오), 출력 2 (스테레오)
    setAudioChannels(2, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    juce::Logger::writeToLog("Audio prepared!");

    int delayBufferSize = static_cast<int>(sampleRate * 2.0); // 2초짜리 버퍼
    delayBuffer.setSize(2, delayBufferSize); // 스테레오
    delayBuffer.clear();

    writePosition = 0;

    // 0.5초 지연 = 0.5초 만큼 뒤에서 읽기 시작
    int delaySamples = static_cast<int>(sampleRate * 0.5);
    readPosition = (writePosition + delayBufferSize - delaySamples) % delayBufferSize;
}


void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    int numChannels = buffer->getNumChannels();
    int numSamples = bufferToFill.numSamples;
    int delayBufferSize = delayBuffer.getNumSamples();

    float gain = gainSlider.getValue();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer->getWritePointer(channel, bufferToFill.startSample);
        float* delayData = delayBuffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float in = buffer->getSample(channel, sample);
            float delayed = delayData[readPosition];

            float out = in;

            if (useDelay)
                out += delayed * 0.5f;

            out *= gain;
            channelData[sample] = out;

            delayData[writePosition] = in;

            writePosition = (writePosition + 1) % delayBufferSize;
            readPosition = (readPosition + 1) % delayBufferSize;
        }
    }
}


void MainComponent::releaseResources()
{
    juce::Logger::writeToLog("Audio stopped!");
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    gainSlider.setBounds(40, 40, getWidth() - 80, 40);
}
