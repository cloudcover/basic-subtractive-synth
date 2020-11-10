#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class OscillatorView : public juce::Component
{
public:
    OscillatorView(BasicsubtractivesynthAudioProcessor&);
    ~OscillatorView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasicsubtractivesynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorView)

public:
    juce::ComboBox typeMenu;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeMenuValue;
};
