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
    
    Envelope env1Gui;
    Envelope env2Gui;

    Filter flt1Gui;
    Filter flt2Gui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessorEditor)
};
