/*
  ==============================================================================

    RoboticizationEffect.h
    Created: 23 Dec 2025 4:26:05pm
    Author:  mathd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RoboticizationEffect
{
public:
    RoboticizationEffect();
    ~RoboticizationEffect();
    void reset();
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::AudioBlock<float>& block);

private:
	//juce::dsp::ProcessSpec processSpec;
};