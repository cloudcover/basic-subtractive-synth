/*
  ==============================================================================

    Filter.h
    Created: 5 Oct 2020 11:41:39am
    Author:  nicks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(BasicsubtractivesynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)

public:
    juce::ComboBox typeMenu;
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeMenuValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceSliderValue;
};
