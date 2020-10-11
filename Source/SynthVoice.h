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
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    //=================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
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
    
    //=================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //=================================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    // ================ other functions ================
    
    void getOscType(float* selection)
    {
        theWave = *selection;
    }
    
    //=================================================
    
    double setOscType()
    {
        switch (theWave)
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
        filterChoice = *filterType;
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    
    //=================================================
    
private:
    double level;
    double frequency;
    int theWave;
    
    int filterChoice;
    float cutoff;
    float resonance;
    
    maxiOsc osc1;
    maxiEnv env1;
};
