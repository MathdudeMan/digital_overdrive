/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OverdriveAudioProcessorEditor::OverdriveAudioProcessorEditor (OverdriveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(400, 200);

	//getLookAndFeel().setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::yellow);

	// Parameter Attachments
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

	driveAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DRIVE", driveKnob);
	toneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "TONE", toneKnob);
	levelAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "LEVEL", levelKnob);
	
	// ==========================================

	// Drive Knob
	driveKnob.setSliderStyle(juce::Slider::Rotary);
	//driveKnob.setValue(30.0);
	driveKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&driveKnob);

	// Drive Label
	driveLabel.setText("Drive", juce::dontSendNotification);
	addAndMakeVisible(driveLabel);

	// Tone Knob
	toneKnob.setSliderStyle(juce::Slider::Rotary);
	//toneKnob.setValue(500.0);
	toneKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&toneKnob);

	// Tone Label
	toneLabel.setText("Tone", juce::dontSendNotification);
	addAndMakeVisible(toneLabel);

	// Level Knob
	levelKnob.setSliderStyle(juce::Slider::Rotary);
	//levelKnob.setValue(-20.0);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&levelKnob);

	// Level Label
	levelLabel.setText("Level", juce::dontSendNotification);
	addAndMakeVisible(levelLabel);

}

OverdriveAudioProcessorEditor::~OverdriveAudioProcessorEditor()
{
}

//==============================================================================
void OverdriveAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Overdrive Pedal", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void OverdriveAudioProcessorEditor::resized()
{
	driveKnob.setBounds(50, 50, 100, 100);
	driveLabel.setBounds(100, 150, 100, 20);

	toneKnob.setBounds(160, 80, 100, 100);
	toneLabel.setBounds(210, 70, 100, 20);

	levelKnob.setBounds(270, 50, 100, 100);
	levelLabel.setBounds(320, 150, 100, 20);

}
