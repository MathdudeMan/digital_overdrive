/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OverdriveAudioProcessor::OverdriveAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
	    apvts(*this, nullptr, "PARAMETERS",
            {
                std::make_unique<juce::AudioParameterFloat>("DRIVE", "Drive", juce::NormalisableRange<float>(0.0f, 100.0f), 30.0f),
                std::make_unique<juce::AudioParameterFloat>("TONE", "Tone", juce::NormalisableRange<float>(500.0f, 20000.0f, 1.0f, 0.2f), 16000.0f),
				std::make_unique<juce::AudioParameterFloat>("LEVEL", "Level", juce::NormalisableRange<float>(-60.0f, 0.0f, 1.0f, 2.0f), -10.0f),
            })
{

}

OverdriveAudioProcessor::~OverdriveAudioProcessor()
{
}

//==============================================================================
const juce::String OverdriveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OverdriveAudioProcessor::acceptsMidi() const
{
    return false;
}

bool OverdriveAudioProcessor::producesMidi() const
{
    return false;
}

bool OverdriveAudioProcessor::isMidiEffect() const
{
    return false;
}

double OverdriveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OverdriveAudioProcessor::getNumPrograms()
{
    return 1; 
}

int OverdriveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OverdriveAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OverdriveAudioProcessor::getProgramName (int index)
{
    return {};
}

void OverdriveAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OverdriveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const auto channels = juce::jmax(getTotalNumInputChannels(), getTotalNumOutputChannels());

    if (channels == 0)
        return;

	// ====================

    // Set Drive knob params
    auto& preGain = overdriveChain.template get<driveGain>();
	preGain.setGainDecibels(30.0f);
	//preGain.setGainDecibels(*apvts.getRawParameterValue("DRIVE"));

    // Set waveshaper params
    overdriveChain.get<waveShaper>().functionToUse = [] (float x)
    {
        return std::tanh(x);
	};

    // Set tone knob params
	auto& toneFilter = overdriveChain.template get<toneLowPass>();
    *toneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 8000.0f);
	//*toneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, *apvts.getRawParameterValue("TONE"));

	// Set Level knob params
    auto& postGain = overdriveChain.template get<levelGain>();
	postGain.setGainDecibels(-10.0f);
	//postGain.setGainDecibels(*apvts.getRawParameterValue("LEVEL"));

    // ====================

	overdriveChain.reset();
    overdriveChain.prepare({ sampleRate, (juce::uint32)samplesPerBlock, (juce::uint32)channels });

    reset();
}

void OverdriveAudioProcessor::releaseResources()
{
	overdriveChain.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OverdriveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;

}
#endif

void OverdriveAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (juce::jmax(getTotalNumInputChannels(), getTotalNumOutputChannels()) == 0)
        return;

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    updateKnobs();

	// Create audio block from buffer and process thru DSP chain
	auto inoutBlock = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, (size_t)totalNumInputChannels);
    overdriveChain.process(juce::dsp::ProcessContextReplacing<float>(inoutBlock));

}

void OverdriveAudioProcessor::updateKnobs()
{
    auto& preGain = overdriveChain.template get<driveGain>();
    preGain.setGainDecibels(*apvts.getRawParameterValue("DRIVE"));

    auto& toneFilter = overdriveChain.template get<toneLowPass>();
    *toneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), *apvts.getRawParameterValue("TONE"));

    auto& postGain = overdriveChain.template get<levelGain>();
    postGain.setGainDecibels(*apvts.getRawParameterValue("LEVEL"));
}

//==============================================================================
bool OverdriveAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* OverdriveAudioProcessor::createEditor()
{
    return new OverdriveAudioProcessorEditor (*this);
}

//==============================================================================
void OverdriveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void OverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
		apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OverdriveAudioProcessor();
}
