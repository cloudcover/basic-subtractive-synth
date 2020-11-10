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
