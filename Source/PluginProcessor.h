/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

#define ENV1_ATTACK_ID "env1-attack"
#define ENV1_ATTACK_NAME "Env 1 Attack"
#define ENV1_DECAY_ID "env1-decay"
#define ENV1_DECAY_NAME "Env 1 Decay"
#define ENV1_SUSTAIN_ID "env1-sustain"
#define ENV1_SUSTAIN_NAME "Env 1 Sustain"
#define ENV1_RELEASE_ID "env1-release"
#define ENV1_RELEASE_NAME "Env 1 Release"

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessor)
};
