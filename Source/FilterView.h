#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FilterView : public juce::Component
{
public:
    FilterView(BasicSubtractiveSynthAudioProcessor&);
    ~FilterView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicSubtractiveSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterView)

public:
    juce::ComboBox typeMenu;
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeMenuValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceSliderValue;
};
