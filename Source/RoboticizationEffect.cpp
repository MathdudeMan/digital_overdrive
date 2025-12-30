/*
  ==============================================================================

    RoboticizationEffect.cpp
    Created: 23 Dec 2025 4:26:05pm
    Author:  mathd

  ==============================================================================
*/

#include "RoboticizationEffect.h"

RoboticizationEffect::RoboticizationEffect()
{
}

RoboticizationEffect::~RoboticizationEffect()
{
}

void RoboticizationEffect::reset()
{
}

void RoboticizationEffect::prepare(const juce::dsp::ProcessSpec& spec)
{

}

void RoboticizationEffect::process(juce::dsp::AudioBlock<float>& block)
{
    auto numSamples = block.getNumSamples();
    auto numChannels = block.getNumChannels();
    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);

		juce::dsp::FFT fft(10); // 1024-point FFT

        for (size_t sample = 0; sample < numSamples; ++sample)
        {
            float inputSample = channelData[sample];
            // Simple roboticization effect: hard clipping
            if (inputSample > 0.5f)
                inputSample = 0.5f;
            else if (inputSample < -0.5f)
                inputSample = -0.5f;
            channelData[sample] = inputSample;
        }
    }
}