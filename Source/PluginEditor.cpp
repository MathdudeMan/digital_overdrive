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
    setSize(350, 200);
	
	// Custom Look And Feel
	auto* squareLAF = new CircleLookAndFeel();
	setupSquareLookAndFeelColours(*squareLAF);
	setLookAndFeel(squareLAF);

	// ==========================================

	// Parameter Attachments
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

	driveAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DRIVE", driveKnob);
	toneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "TONE", toneKnob);
	levelAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "LEVEL", levelKnob);
	
	// ==========================================

	juce::Font labelFont = juce::Font("Bahnschrift", 16.0f, juce::Font::bold);

	// Drive Knob
	driveKnob.setSliderStyle(juce::Slider::Rotary);
	driveKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&driveKnob);

	// Drive Label
	driveLabel.setText("DRIVE", juce::dontSendNotification);
	driveLabel.setFont(labelFont);
	driveLabel.setJustificationType(juce::Justification::centredTop);
	addAndMakeVisible(driveLabel);

	// Tone Knob
	toneKnob.setSliderStyle(juce::Slider::Rotary);
	toneKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&toneKnob);

	// Tone Label
	toneLabel.setText("TONE", juce::dontSendNotification);
	//toneLabel.attachToComponent(&toneKnob, false);
	toneLabel.setFont(labelFont);
	toneLabel.setJustificationType(juce::Justification::centredBottom);
	addAndMakeVisible(toneLabel);

	// Level Knob
	levelKnob.setSliderStyle(juce::Slider::Rotary);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&levelKnob);

	// Level Label
	levelLabel.setText("LEVEL", juce::dontSendNotification);
	levelLabel.setFont(labelFont);
	levelLabel.setJustificationType(juce::Justification::centredTop);
	addAndMakeVisible(levelLabel);

}

OverdriveAudioProcessorEditor::~OverdriveAudioProcessorEditor()
{
}

//==============================================================================
void OverdriveAudioProcessorEditor::paint (juce::Graphics& g)
{
	// Draw Background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	// Draw Title
	g.setColour(getLookAndFeel().findColour(juce::Label::textColourId));
	g.setFont(juce::Font("Bahnschrift", 36.0f, juce::Font::bold));
    g.drawFittedText ("OverDrive", 0, 20, getWidth(), 30, juce::Justification::centred, 1);
}

void OverdriveAudioProcessorEditor::resized()
{
	int midpoint = getWidth() / 2;

	driveKnob.setBounds(midpoint - 140, getHeight() - 140, 100, 100);
	driveLabel.setBounds(midpoint - 140, getHeight() - 50, 100, 20);

	toneKnob.setBounds(midpoint - 50, getHeight() - 110, 100, 100);
	toneLabel.setBounds(midpoint - 50, getHeight() - 120, 100, 20);

	levelKnob.setBounds(midpoint + 40, getHeight() - 140, 100, 100);
	levelLabel.setBounds(midpoint + 40, getHeight() - 50, 100, 20);

} 

// =============================================================================

void OverdriveAudioProcessorEditor::setupSquareLookAndFeelColours(LookAndFeel& laf)
{
	auto baseColour = Colours::black;

	laf.setColour(ResizableWindow::backgroundColourId, Colours::yellow);
	laf.setColour(Label::textColourId, Colours::black);

	laf.setColour(Slider::thumbColourId, Colour::greyLevel(0.95f));
	laf.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
	laf.setColour(Slider::rotarySliderFillColourId, baseColour);
	laf.setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	laf.setColour(Slider::trackColourId, Colours::black);

	laf.setColour(TextButton::buttonColourId, Colours::white);
	laf.setColour(TextButton::textColourOffId, baseColour);

	laf.setColour(TextButton::buttonOnColourId, laf.findColour(TextButton::textColourOffId));
	laf.setColour(TextButton::textColourOnId, laf.findColour(TextButton::buttonColourId));

}