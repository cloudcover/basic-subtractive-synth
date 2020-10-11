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
    mySynth.clearVoices();
    
    for (int i = 0; i < 16; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
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
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    filter1.reset();
    filter2.reset();
    
    filter1.prepare(spec);
    filter2.prepare(spec);
    
    updateFilters();
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

void BasicsubtractivesynthAudioProcessor::updateFilters()
{
    int flt1_type = *treeState.getRawParameterValue(FLT1_TYPE_ID);
    int flt1_cutoff = *treeState.getRawParameterValue(FLT1_CUTOFF_ID);
    int flt1_resonance = *treeState.getRawParameterValue(FLT1_RESONANCE_ID);
    
    if (flt1_type == 0)
    {
        filter1.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        filter1.state->setCutOffFrequency(lastSampleRate, flt1_cutoff, flt1_resonance);
    }
    else if (flt1_type == 1)
    {
        filter1.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        filter1.state->setCutOffFrequency(lastSampleRate, flt1_cutoff, flt1_resonance);
    }
    else if (flt1_type == 2)
    {
        filter1.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        filter1.state->setCutOffFrequency(lastSampleRate, flt1_cutoff, flt1_resonance);
    }
    
    int flt2_type = *treeState.getRawParameterValue(FLT2_TYPE_ID);
    int flt2_cutoff = *treeState.getRawParameterValue(FLT2_CUTOFF_ID);
    int flt2_resonance = *treeState.getRawParameterValue(FLT2_RESONANCE_ID);
    
    if (flt2_type == 0)
    {
        filter2.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        filter2.state->setCutOffFrequency(lastSampleRate, flt2_cutoff, flt2_resonance);
    }
    else if (flt2_type == 1)
    {
        filter2.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        filter2.state->setCutOffFrequency(lastSampleRate, flt2_cutoff, flt2_resonance);
    }
    else if (flt2_type == 2)
    {
        filter2.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        filter2.state->setCutOffFrequency(lastSampleRate, flt2_cutoff, flt2_resonance);
    }
}

void BasicsubtractivesynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            // workaround suggested in YouTube comments
            float* env1_attackPtr = (float*) treeState.getRawParameterValue(ENV1_ATTACK_ID);
            float* env1_decayPtr = (float*) treeState.getRawParameterValue(ENV1_DECAY_ID);
            float* env1_sustainPtr = (float*) treeState.getRawParameterValue(ENV1_SUSTAIN_ID);
            float* env1_releasePtr = (float*) treeState.getRawParameterValue(ENV1_RELEASE_ID);
            myVoice->setEnv1Params(env1_attackPtr, env1_decayPtr, env1_sustainPtr, env1_releasePtr);
            
            float* env2_attackPtr = (float*) treeState.getRawParameterValue(ENV2_ATTACK_ID);
            float* env2_decayPtr = (float*) treeState.getRawParameterValue(ENV2_DECAY_ID);
            float* env2_sustainPtr = (float*) treeState.getRawParameterValue(ENV2_SUSTAIN_ID);
            float* env2_releasePtr = (float*) treeState.getRawParameterValue(ENV2_RELEASE_ID);
            myVoice->setEnv2Params(env2_attackPtr, env2_decayPtr, env2_sustainPtr, env2_releasePtr);
            
            float* osc1_typePtr = (float*) treeState.getRawParameterValue(OSC1_TYPE_ID);
            myVoice->setOsc1Type(osc1_typePtr);
            
            float* osc2_typePtr = (float*) treeState.getRawParameterValue(OSC2_TYPE_ID);
            myVoice->setOsc2Type(osc2_typePtr);
            
            float* flt1_typePtr = (float*) treeState.getRawParameterValue(FLT1_TYPE_ID);
            float* flt1_cutoffPtr = (float*) treeState.getRawParameterValue(FLT1_CUTOFF_ID);
            float* flt1_resonancePtr = (float*) treeState.getRawParameterValue(FLT1_RESONANCE_ID);
            myVoice->setFlt1Params(flt1_typePtr, flt1_cutoffPtr, flt1_resonancePtr);
            
            float* flt2_typePtr = (float*) treeState.getRawParameterValue(FLT2_TYPE_ID);
            float* flt2_cutoffPtr = (float*) treeState.getRawParameterValue(FLT2_CUTOFF_ID);
            float* flt2_resonancePtr = (float*) treeState.getRawParameterValue(FLT2_RESONANCE_ID);
            myVoice->setFlt1Params(flt2_typePtr, flt2_cutoffPtr, flt2_resonancePtr);
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilters();
    
    juce::dsp::AudioBlock<float> block(buffer);
    
    // TODO: mySynth.renderNextBlock is handing over the sum of both oscillators, so we are unable
    // to make use of the second filter. Figure out a solution for this.
    filter1.process(juce::dsp::ProcessContextReplacing<float>(block));
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
