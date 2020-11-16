#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MixerView : public juce::Component
{
public:
    MixerView(BasicSubtractiveSynthAudioProcessor&);
    ~MixerView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicSubtractiveSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerView)
    
public:
    juce::Slider osc1Slider;
    juce::Slider osc2Slider;
    juce::Slider osc3Slider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1SliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2SliderValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc3SliderValue;
};
