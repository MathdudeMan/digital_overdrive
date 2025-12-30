/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class OverdriveAudioProcessor  : public juce::AudioProcessor,
	                             private juce::ValueTree::Listener
{
public:
    //==============================================================================
    OverdriveAudioProcessor();
    ~OverdriveAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

private:
    //==============================================================================

    enum {
        driveGain,
        waveShaper,
        toneLowPass,
        levelGain
    };

	using IIREffect = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;
	juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, IIREffect, juce::dsp::Gain<float>> overdriveChain;

    void updateKnobs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveAudioProcessor)
};
