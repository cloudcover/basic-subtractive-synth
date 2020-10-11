/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

#define OSC1_TYPE_ID "osc1-type"
#define OSC1_TYPE_NAME "Osc 1 Type"
#define OSC2_TYPE_ID "osc2-type"
#define OSC2_TYPE_NAME "Osc 2 Type"

#define ENV1_ATTACK_ID "env1-attack"
#define ENV1_ATTACK_NAME "Env 1 Attack"
#define ENV1_DECAY_ID "env1-decay"
#define ENV1_DECAY_NAME "Env 1 Decay"
#define ENV1_SUSTAIN_ID "env1-sustain"
#define ENV1_SUSTAIN_NAME "Env 1 Sustain"
#define ENV1_RELEASE_ID "env1-release"
#define ENV1_RELEASE_NAME "Env 1 Release"

#define ENV2_ATTACK_ID "env2-attack"
#define ENV2_ATTACK_NAME "Env 2 Attack"
#define ENV2_DECAY_ID "env2-decay"
#define ENV2_DECAY_NAME "Env 2 Decay"
#define ENV2_SUSTAIN_ID "env2-sustain"
#define ENV2_SUSTAIN_NAME "Env 2 Sustain"
#define ENV2_RELEASE_ID "env2-release"
#define ENV2_RELEASE_NAME "Env 2 Release"

#define FLT1_TYPE_ID "flt1-type"
#define FLT1_TYPE_NAME "Flt 1 Type"
#define FLT1_CUTOFF_ID "flt1-cutoff"
#define FLT1_CUTOFF_NAME "Flt 1 Cutoff"
#define FLT1_RESONANCE_ID "flt1-resonance"
#define FLT1_RESONANCE_NAME "Flt 1 Resonance"

#define FLT2_TYPE_ID "flt2-type"
#define FLT2_TYPE_NAME "Flt 2 Type"
#define FLT2_CUTOFF_ID "flt2-cutoff"
#define FLT2_CUTOFF_NAME "Flt 2 Cutoff"
#define FLT2_RESONANCE_ID "flt2-resonance"
#define FLT2_RESONANCE_NAME "Flt 2 Resonance"

//==============================================================================
/**
*/
class BasicsubtractivesynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BasicsubtractivesynthAudioProcessor();
    ~BasicsubtractivesynthAudioProcessor() override;

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

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    void updateFilters();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessor)
    
    juce::Synthesiser mySynth;
    SynthVoice* myVoice;
    
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> filter1;
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> filter2;
    
    // We're not using this for anything yet, we're just storing it as a best practice for handling sample rate changes in the future.
    double lastSampleRate;
};
