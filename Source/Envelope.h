/*
  ==============================================================================

    Envelope.h
    Created: 5 Oct 2020 11:41:07am
    Author:  nicks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(BasicsubtractivesynthAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)

public:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    // Component attachments need to come last because destruction happens from the bottom of the file upwards
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainSliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderValue;
};
