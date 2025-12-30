/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OverdriveAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    OverdriveAudioProcessorEditor (OverdriveAudioProcessor&);
    ~OverdriveAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    OverdriveAudioProcessor& audioProcessor;

    juce::Slider driveKnob;
    juce::Slider toneKnob;
	juce::Slider levelKnob;

	juce::Label driveLabel;
	juce::Label toneLabel;
	juce::Label levelLabel;

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	std::unique_ptr<SliderAttachment> driveAttachment;
	std::unique_ptr<SliderAttachment> toneAttachment;
	std::unique_ptr<SliderAttachment> levelAttachment;
    
	//juce::LookAndFeel_V4 otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveAudioProcessorEditor)
};
