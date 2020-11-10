#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

#define OSC1_TYPE_ID "osc1-type"
#define OSC1_TYPE_NAME "Osc 1 Type"
#define OSC1_LEVEL_ID "osc1-level"
#define OSC1_LEVEL_NAME "Osc 1 Level"
#define OSC2_TYPE_ID "osc2-type"
#define OSC2_TYPE_NAME "Osc 2 Type"
#define OSC2_LEVEL_ID "osc2-level"
#define OSC2_LEVEL_NAME "Osc 2 Level"
#define OSC3_TYPE_ID "osc3-type"
#define OSC3_TYPE_NAME "Osc 3 Type"
#define OSC3_LEVEL_ID "osc3-level"
#define OSC3_LEVEL_NAME "Osc 3 Level"

#define FLT_TYPE_ID "flt-type"
#define FLT_TYPE_NAME "Flt Type"
#define FLT_CUTOFF_ID "flt-cutoff"
#define FLT_CUTOFF_NAME "Flt Cutoff"
#define FLT_RESONANCE_ID "flt-resonance"
#define FLT_RESONANCE_NAME "Flt Resonance"

#define FLT_ENV_ATTACK_ID "flt-env-attack"
#define FLT_ENV_ATTACK_NAME "Filter Env Attack"
#define FLT_ENV_DECAY_ID "flt-env-decay"
#define FLT_ENV_DECAY_NAME "Filter Env Decay"
#define FLT_ENV_SUSTAIN_ID "flt-env-sustain"
#define FLT_ENV_SUSTAIN_NAME "Filter Env Sustain"
#define FLT_ENV_RELEASE_ID "flt-env-release"
#define FLT_ENV_RELEASE_NAME "Filter Env Release"

#define AMP_ENV_ATTACK_ID "amp-env-attack"
#define AMP_ENV_ATTACK_NAME "Amp Env Attack"
#define AMP_ENV_DECAY_ID "amp-env-decay"
#define AMP_ENV_DECAY_NAME "Amp Env Decay"
#define AMP_ENV_SUSTAIN_ID "amp-env-sustain"
#define AMP_ENV_SUSTAIN_NAME "Amp Env Sustain"
#define AMP_ENV_RELEASE_ID "amp-env-release"
#define AMP_ENV_RELEASE_NAME "Amp Env Release"

class BasicsubtractivesynthAudioProcessor  : public juce::AudioProcessor
{
public:
    BasicsubtractivesynthAudioProcessor();
    ~BasicsubtractivesynthAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    void updateFilter();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessor)
    
    juce::Synthesiser mySynth;
    
    // This is a pointer because it's essentially a template, as I understand it.
    SynthVoice* myVoice;
    
    // TODO: Can this be relocated somewhere where it makes more sense, like inside of SynthVoice?
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> filter;
    
    double lastSampleRate;
};
