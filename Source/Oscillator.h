/*
  ==============================================================================

    Oscillator.h
    Created: 5 Oct 2020 11:41:57am
    Author:  nicks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator(BasicsubtractivesynthAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)

public:
    juce::ComboBox typeMenu;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeMenuValue;
};
