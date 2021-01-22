#include "PluginProcessor.h"
#include "PluginEditor.h"

BasicSubtractiveSynthAudioProcessor::BasicSubtractiveSynthAudioProcessor()
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

BasicSubtractiveSynthAudioProcessor::~BasicSubtractiveSynthAudioProcessor() { }

juce::AudioProcessorValueTreeState::ParameterLayout BasicSubtractiveSynthAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    auto osc1TypeParam = std::make_unique<juce::AudioParameterFloat>(OSC1_TYPE_ID, OSC1_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(osc1TypeParam));
    auto osc1LevelParam = std::make_unique<juce::AudioParameterFloat>(OSC1_LEVEL_ID, OSC1_LEVEL_NAME, 0.0f, 1.0f, 0.5f);
    params.push_back(std::move(osc1LevelParam));
    auto osc1OctaveParam = std::make_unique<juce::AudioParameterInt>(OSC1_OCTAVE_ID, OSC1_LEVEL_ID, 1, 5, 3);
    params.push_back(std::move(osc1OctaveParam));
    
    auto osc2TypeParam = std::make_unique<juce::AudioParameterFloat>(OSC2_TYPE_ID, OSC2_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(osc2TypeParam));
    auto osc2LevelParam = std::make_unique<juce::AudioParameterFloat>(OSC2_LEVEL_ID, OSC2_LEVEL_NAME, 0.0f, 1.0f, 0.5f);
    params.push_back(std::move(osc2LevelParam));
    auto osc2OctaveParam = std::make_unique<juce::AudioParameterInt>(OSC2_OCTAVE_ID, OSC2_OCTAVE_NAME, 1, 5, 3);
    params.push_back(std::move(osc2OctaveParam));
    
    auto osc3TypeParam = std::make_unique<juce::AudioParameterFloat>(OSC3_TYPE_ID, OSC3_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(osc3TypeParam));
    auto osc3LevelParam = std::make_unique<juce::AudioParameterFloat>(OSC3_LEVEL_ID, OSC3_LEVEL_NAME, 0.0f, 1.0f, 0.5f);
    params.push_back(std::move(osc3LevelParam));
    auto osc3OctaveParam = std::make_unique<juce::AudioParameterInt>(OSC3_OCTAVE_ID, OSC3_OCTAVE_NAME, 1, 5, 3);
    params.push_back(std::move(osc3OctaveParam));
    
    auto fltTypeParam = std::make_unique<juce::AudioParameterFloat>(FLT_TYPE_ID, FLT_TYPE_NAME, 0.0f, 2.0f, 0.0f);
    params.push_back(std::move(fltTypeParam));
    // THIS is how to work around that issue with skewing the dial on a value that's tied into an AudioProcessorValueTreeState.
    juce::NormalisableRange<float> cutoffRange(20.0f, 20000.0f);
    cutoffRange.setSkewForCentre(1000.0f);
    auto fltCutoffParam = std::make_unique<juce::AudioParameterFloat>(FLT_CUTOFF_ID, FLT_CUTOFF_NAME, cutoffRange, 1000.0f, "Hz");
    params.push_back(std::move(fltCutoffParam));
    auto fltResonanceParam = std::make_unique<juce::AudioParameterFloat>(FLT_RESONANCE_ID, FLT_RESONANCE_NAME, 1.0f, 5.0f, 1.0f);
    params.push_back(std::move(fltResonanceParam));
    
    auto envAttackParam = std::make_unique<juce::AudioParameterFloat>(ENV_ATTACK_ID, ENV_ATTACK_NAME, 0.1f, 5000.0f, 100.0f);
    params.push_back(std::move(envAttackParam));
    auto envDecayParam = std::make_unique<juce::AudioParameterFloat>(ENV_DECAY_ID, ENV_DECAY_NAME, 1.0f, 2000.0f, 100.0f);
    params.push_back(std::move(envDecayParam));
    auto envSustainParam = std::make_unique<juce::AudioParameterFloat>(ENV_SUSTAIN_ID, ENV_SUSTAIN_NAME, 0.0f, 1.0f, 0.8f);
    params.push_back(std::move(envSustainParam));
    auto envReleaseParam = std::make_unique<juce::AudioParameterFloat>(ENV_RELEASE_ID, ENV_RELEASE_NAME, 0.1f, 5000.0f, 1000.0f);
    params.push_back(std::move(envReleaseParam));

    return { params.begin(), params.end() };
}

const juce::String BasicSubtractiveSynthAudioProcessor::getName() const { return JucePlugin_Name; }

bool BasicSubtractiveSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicSubtractiveSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicSubtractiveSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicSubtractiveSynthAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int BasicSubtractiveSynthAudioProcessor::getNumPrograms() { return 1; }
int BasicSubtractiveSynthAudioProcessor::getCurrentProgram() { return 0; }
void BasicSubtractiveSynthAudioProcessor::setCurrentProgram (int index) { }
const juce::String BasicSubtractiveSynthAudioProcessor::getProgramName (int index) { return {}; }
void BasicSubtractiveSynthAudioProcessor::changeProgramName (int index, const juce::String& newName) { }

void BasicSubtractiveSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    filter.reset();
    filter.prepare(spec);
    updateFilter();
}

void BasicSubtractiveSynthAudioProcessor::releaseResources() { }

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicSubtractiveSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicSubtractiveSynthAudioProcessor::updateFilter()
{
    int flt_type = *treeState.getRawParameterValue(FLT_TYPE_ID);
    int flt_cutoff = *treeState.getRawParameterValue(FLT_CUTOFF_ID);
    int flt_resonance = *treeState.getRawParameterValue(FLT_RESONANCE_ID);
    
    if (flt_type == 0)
    {
        filter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        filter.state->setCutOffFrequency(lastSampleRate, flt_cutoff, flt_resonance);
    }
    else if (flt_type == 1)
    {
        filter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        filter.state->setCutOffFrequency(lastSampleRate, flt_cutoff, flt_resonance);
    }
    else if (flt_type == 2)
    {
        filter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        filter.state->setCutOffFrequency(lastSampleRate, flt_cutoff, flt_resonance);
    }
}

void BasicSubtractiveSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            // workaround suggested in YouTube comments
            float* osc1_typePtr = (float*) treeState.getRawParameterValue(OSC1_TYPE_ID);
            myVoice->setOsc1Type(osc1_typePtr);
            
            float* osc2_typePtr = (float*) treeState.getRawParameterValue(OSC2_TYPE_ID);
            myVoice->setOsc2Type(osc2_typePtr);
            
            float* osc3_typePtr = (float*) treeState.getRawParameterValue(OSC3_TYPE_ID);
            myVoice->setOsc3Type(osc3_typePtr);
            
            int* osc1_octavePtr = (int*) treeState.getRawParameterValue(OSC1_OCTAVE_ID);
            myVoice->setOsc1OctaveOffset(osc1_octavePtr);
            
            int* osc2_octavePtr = (int*) treeState.getRawParameterValue(OSC2_OCTAVE_ID);
            myVoice->setOsc2OctaveOffset(osc2_octavePtr);
            
            int* osc3_octavePtr = (int*) treeState.getRawParameterValue(OSC3_OCTAVE_ID);
            myVoice->setOsc3OctaveOffset(osc3_octavePtr);
            
            float* osc1_levelPtr = (float*) treeState.getRawParameterValue(OSC1_LEVEL_ID);
            float* osc2_levelPtr = (float*) treeState.getRawParameterValue(OSC2_LEVEL_ID);
            float* osc3_levelPtr = (float*) treeState.getRawParameterValue(OSC3_LEVEL_ID);
            myVoice->setOscLevels(osc1_levelPtr, osc2_levelPtr, osc3_levelPtr);
            
            float* flt_typePtr = (float*) treeState.getRawParameterValue(FLT_TYPE_ID);
            float* flt_cutoffPtr = (float*) treeState.getRawParameterValue(FLT_CUTOFF_ID);
            float* flt_resonancePtr = (float*) treeState.getRawParameterValue(FLT_RESONANCE_ID);
            myVoice->setFltParams(flt_typePtr, flt_cutoffPtr, flt_resonancePtr);
            
            float* env_attackPtr = (float*) treeState.getRawParameterValue(ENV_ATTACK_ID);
            float* env_decayPtr = (float*) treeState.getRawParameterValue(ENV_DECAY_ID);
            float* env_sustainPtr = (float*) treeState.getRawParameterValue(ENV_SUSTAIN_ID);
            float* env_releasePtr = (float*) treeState.getRawParameterValue(ENV_RELEASE_ID);
            myVoice->setEnvParams(env_attackPtr, env_decayPtr, env_sustainPtr, env_releasePtr);
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilter();
    
    juce::dsp::AudioBlock<float> block(buffer);
    
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

bool BasicSubtractiveSynthAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* BasicSubtractiveSynthAudioProcessor::createEditor() { return new BasicSubtractiveSynthAudioProcessorEditor (*this); }
void BasicSubtractiveSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData) { }
void BasicSubtractiveSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) { }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new BasicSubtractiveSynthAudioProcessor(); }
