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

	getLookAndFeel().setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::yellow);

	// Parameter Attachments
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

	driveAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DRIVE", driveKnob);
	toneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "TONE", toneKnob);
	levelAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "LEVEL", levelKnob);
	
	// ==========================================

	juce::Font labelFont = juce::Font(16.0f, juce::Font::bold));

	// Drive Knob
	driveKnob.setSliderStyle(juce::Slider::Rotary);
	driveKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&driveKnob);

	// Drive Label
	driveLabel.setText("Drive", juce::dontSendNotification);
	driveLabel.attachToComponent(&driveKnob, false);
	driveLabel.setFont(labelFont);
	driveLabel.setJustificationType(juce::Justification::centred);
	driveLabel.setColour(juce::Label::textColourId, juce::Colours::black);
	addAndMakeVisible(driveLabel);

	// Tone Knob
	toneKnob.setSliderStyle(juce::Slider::Rotary);
	toneKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&toneKnob);

	// Tone Label
	toneLabel.setText("Tone", juce::dontSendNotification);
	toneLabel.setFont(labelFont);
	toneLabel.setJustificationType(juce::Justification::centred);
	toneLabel.setColour(juce::Label::textColourId, juce::Colours::black);
	addAndMakeVisible(toneLabel);

	// Level Knob
	levelKnob.setSliderStyle(juce::Slider::Rotary);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&levelKnob);

	// Level Label
	levelLabel.setText("Level", juce::dontSendNotification);
	levelLabel.attachToComponent(&levelKnob, false);
	levelLabel.setFont(labelFont);
	levelLabel.setJustificationType(juce::Justification::centred);
	levelLabel.setColour(juce::Label::textColourId, juce::Colours::black);
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
	g.setFont(juce::Font(30.0f, juce::Font::bold));
    g.drawFittedText ("Overdrive Pedal", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void OverdriveAudioProcessorEditor::resized()
{
	driveKnob.setBounds(50, 50, 100, 100);

	toneKnob.setBounds(160, 80, 100, 100);
	toneLabel.setBounds(210, 70, 100, 20);

	levelKnob.setBounds(270, 50, 100, 100);

}
