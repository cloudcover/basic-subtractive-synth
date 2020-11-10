#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EnvelopeView.h"
#include "FilterView.h"
#include "OscillatorView.h"

class BasicsubtractivesynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    BasicsubtractivesynthAudioProcessorEditor (BasicsubtractivesynthAudioProcessor&);
    ~BasicsubtractivesynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    
    OscillatorView osc1Gui;
    OscillatorView osc2Gui;
    OscillatorView osc3Gui;

    EnvelopeView fltEnvGui;
    EnvelopeView ampEnvGui;

    FilterView fltGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicsubtractivesynthAudioProcessorEditor)
};
