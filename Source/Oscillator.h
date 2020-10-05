/*
  ==============================================================================

    Oscillator.h
    Created: 5 Oct 2020 11:41:57am
    Author:  nicks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator();
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
