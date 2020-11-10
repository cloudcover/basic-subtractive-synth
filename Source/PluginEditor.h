/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Filter.h"
#include "Oscillator.h"

//==============================================================================
/**
*/
class BasicsubtractivesynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BasicsubtractivesynthAudioProcessorEditor (BasicsubtractivesynthAudioProcessor&);
    ~BasicsubtractivesynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    
    // TODO: Rename classes to express that they're views rather than synthesis components? i.e. "OscillatorPanel" instead of just "Oscillator"
    
    Oscillator osc1Gui;
    Oscillator osc2Gui;
    Oscillator osc3Gui;

    Envelope fltEnvGui;
    Envelope ampEnvGui;

    Filter fltGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessorEditor)
};
