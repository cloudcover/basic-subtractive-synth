/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Oct 2020 11:40:19am
    Author:  nicks

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
    public:
    // ================ SynthesiserVoice abstract virtual functions ================
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //=================================================
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        env2.trigger = 1;
        
        // TODO: make actual use of the incoming velocity value.
        level = velocity;
        
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    //=================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        env2.trigger = 0;
        
        // This doesn't make sense - I don't think I need it?
        //allowTailOff = true;
        
        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }
    
    //=================================================
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, setEnvelope() * 0.3f);
            }
            
            ++startSample;
        }
    }
    
    /* RENDERING ORDER:
     setOscType -> setEnvelope() -> renderNextBlock()
     */
    
    //=================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        // no implementation yet
    }
    
    //=================================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        // no implementation yet
    }
    
    // ================ other functions ================
    
    void getOscType(float* selection)
    {
        osc1_waveformType = *selection;
    }
    
    //=================================================
    
    double setOscType()
    {
        switch (osc1_waveformType)
        {
            case 0: return osc1.sinewave(frequency);
            case 1: return osc1.saw(frequency);
            case 2: return osc1.square(frequency);
        }
        
        return osc1.sinewave(frequency);
    }
    
    //=================================================
    
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }
    
    //=================================================
    
    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    //=================================================
    
    void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
    {
        flt1_type = *filterType;
        flt1_cutoff = *filterCutoff;
        flt1_resonance = *filterRes;
    }
    
    //=================================================
    
private:
    double level;
    double frequency;
    
    int osc1_waveformType;
    maxiOsc osc1;
    
    int osc2_waveformType;
    maxiOsc osc2;
    
    int flt1_type;
    float flt1_cutoff;
    float flt1_resonance;
    
    maxiEnv env1;
    maxiEnv env2;
};
