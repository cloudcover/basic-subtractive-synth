/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicsubtractivesynthAudioProcessor::BasicsubtractivesynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // initialize mySynth here
}

BasicsubtractivesynthAudioProcessor::~BasicsubtractivesynthAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout BasicsubtractivesynthAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    auto osc1TypeParam = std::make_unique<juce::AudioParameterFloat>(OSC1_TYPE_ID, OSC1_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(osc1TypeParam));

    auto env1AttackParam = std::make_unique<juce::AudioParameterFloat>(ENV1_ATTACK_ID, ENV1_ATTACK_NAME, 0.1f, 5000.0f, 100.0f);
    params.push_back(std::move(env1AttackParam));
    auto env1DecayParam = std::make_unique<juce::AudioParameterFloat>(ENV1_DECAY_ID, ENV1_DECAY_NAME, 1.0f, 2000.0f, 100.0f);
    params.push_back(std::move(env1DecayParam));
    auto env1SustainParam = std::make_unique<juce::AudioParameterFloat>(ENV1_SUSTAIN_ID, ENV1_SUSTAIN_NAME, 0.0f, 1.0f, 0.8f);
    params.push_back(std::move(env1SustainParam));
    auto env1ReleaseParam = std::make_unique<juce::AudioParameterFloat>(ENV1_RELEASE_ID, ENV1_RELEASE_NAME, 0.1f, 5000.0f, 1000.0f);
    params.push_back(std::move(env1ReleaseParam));

    auto flt1TypeParam = std::make_unique<juce::AudioParameterFloat>(FLT1_TYPE_ID, FLT1_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(flt1TypeParam));

    // THIS is how to work around that issue with skewing the dial on a value that's tied into an AudioProcessorValueTreeState.
    juce::NormalisableRange<float> cutoffRange(20.0f, 20000.0f);
    cutoffRange.setSkewForCentre(1000.0f);
    auto flt1CutoffParam = std::make_unique<juce::AudioParameterFloat>(FLT1_CUTOFF_ID, FLT1_CUTOFF_NAME, cutoffRange, 1000.0f, "Hz");
    params.push_back(std::move(flt1CutoffParam));
    
    auto flt1ResonanceParam = std::make_unique<juce::AudioParameterFloat>(FLT1_RESONANCE_ID, FLT1_RESONANCE_NAME, 1.0f, 5.0f, 1.0f);
    params.push_back(std::move(flt1ResonanceParam));

    auto osc2TypeParam = std::make_unique<juce::AudioParameterFloat>(OSC2_TYPE_ID, OSC2_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(osc2TypeParam));

    auto env2AttackParam = std::make_unique<juce::AudioParameterFloat>(ENV2_ATTACK_ID, ENV2_ATTACK_NAME, 0.1f, 5000.0f, 100.0f);
    params.push_back(std::move(env2AttackParam));
    auto env2DecayParam = std::make_unique<juce::AudioParameterFloat>(ENV2_DECAY_ID, ENV2_DECAY_NAME, 1.0f, 2000.0f, 100.0f);
    params.push_back(std::move(env2DecayParam));
    auto env2SustainParam = std::make_unique<juce::AudioParameterFloat>(ENV2_SUSTAIN_ID, ENV2_SUSTAIN_NAME, 0.0f, 1.0f, 0.8f);
    params.push_back(std::move(env2SustainParam));
    auto env2ReleaseParam = std::make_unique<juce::AudioParameterFloat>(ENV2_RELEASE_ID, ENV2_RELEASE_NAME, 0.1f, 5000.0f, 1000.0f);
    params.push_back(std::move(env2ReleaseParam));

    auto flt2TypeParam = std::make_unique<juce::AudioParameterFloat>(FLT2_TYPE_ID, FLT2_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(flt2TypeParam));

    auto flt2CutoffParam = std::make_unique<juce::AudioParameterFloat>(FLT2_CUTOFF_ID, FLT2_CUTOFF_NAME, cutoffRange, 1000.0f, "Hz");
    params.push_back(std::move(flt2CutoffParam));
    
    auto flt2ResonanceParam = std::make_unique<juce::AudioParameterFloat>(FLT2_RESONANCE_ID, FLT2_RESONANCE_NAME, 1.0f, 5.0f, 1.0f);
    params.push_back(std::move(flt2ResonanceParam));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String BasicsubtractivesynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicsubtractivesynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicsubtractivesynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicsubtractivesynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicsubtractivesynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicsubtractivesynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicsubtractivesynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicsubtractivesynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicsubtractivesynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicsubtractivesynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicsubtractivesynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BasicsubtractivesynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicsubtractivesynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicsubtractivesynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool BasicsubtractivesynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicsubtractivesynthAudioProcessor::createEditor()
{
    return new BasicsubtractivesynthAudioProcessorEditor (*this);
}

//==============================================================================
void BasicsubtractivesynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicsubtractivesynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicsubtractivesynthAudioProcessor();
}
