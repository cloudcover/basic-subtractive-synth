#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EnvelopeView.h"
#include "FilterView.h"
#include "OscillatorView.h"

class BasicSubtractiveSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    BasicSubtractiveSynthAudioProcessorEditor (BasicSubtractiveSynthAudioProcessor&);
    ~BasicSubtractiveSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicSubtractiveSynthAudioProcessor& audioProcessor;
    
    OscillatorView osc1Gui;
    OscillatorView osc2Gui;
    OscillatorView osc3Gui;

    EnvelopeView fltEnvGui;
    EnvelopeView ampEnvGui;

    FilterView fltGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSubtractiveSynthAudioProcessorEditor)
};
