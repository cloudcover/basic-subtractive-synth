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

#define ENV_ATTACK_ID "env-attack"
#define ENV_ATTACK_NAME "Env Attack"
#define ENV_DECAY_ID "env-decay"
#define ENV_DECAY_NAME "Env Decay"
#define ENV_SUSTAIN_ID "env-sustain"
#define ENV_SUSTAIN_NAME "Env Sustain"
#define ENV_RELEASE_ID "env-release"
#define ENV_RELEASE_NAME "Env Release"

class BasicSubtractiveSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    BasicSubtractiveSynthAudioProcessor();
    ~BasicSubtractiveSynthAudioProcessor() override;

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSubtractiveSynthAudioProcessor)
    
    juce::Synthesiser mySynth;
    
    // This is a pointer because it's essentially a template, as I understand it.
    SynthVoice* myVoice;
    
    // TODO: Can this be relocated somewhere where it makes more sense, like inside of SynthVoice?
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> filter;
    
    double lastSampleRate;
};
