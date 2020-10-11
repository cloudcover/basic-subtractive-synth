/*
  ==============================================================================

    SynthSound.h
    Created: 5 Oct 2020 11:40:06am
    Author:  nicks

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber)
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel)
    {
        return true;
    }
};
