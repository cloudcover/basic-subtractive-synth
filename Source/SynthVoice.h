/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Oct 2020 11:40:19am
    Author:  nick.suda@gmail.com

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
                outputBuffer.addSample(channel, startSample, getSummedOscillators());
            }
            
            ++startSample;
        }
    }
    
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
    
    void setOsc1Type(float* selection)
    {
        osc1_waveformType = *selection;
    }
    
    //=================================================
    
    void setOsc2Type(float* selection)
    {
        osc2_waveformType = *selection;
    }
    
    //=================================================
    
    void setOsc3Type(float* selection)
    {
        osc3_waveformType = *selection;
    }
    
    //=================================================
    
    double getOsc1Output()
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
    
    double getOsc2Output()
    {
        switch (osc2_waveformType)
        {
            case 0: return osc2.sinewave(frequency);
            case 1: return osc2.saw(frequency);
            case 2: return osc2.square(frequency);
        }
        
        return osc2.sinewave(frequency);
    }
    
    //=================================================
    
    void setFltEnvParams(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }
    
    //=================================================
    
    void setAmpEnvParams(float* attack, float* decay, float* sustain, float* release)
    {
        env2.setAttack(double(*attack));
        env2.setDecay(double(*decay));
        env2.setSustain(double(*sustain));
        env2.setRelease(double(*release));
    }
    
    //=================================================
    
    void setFltParams(float* filterType, float* filterCutoff, float* filterRes)
    {
        flt1_type = *filterType;
        flt1_cutoff = *filterCutoff;
        flt1_resonance = *filterRes;
    }
    
    //=================================================
    
    void setFlt2Params(float* filterType, float* filterCutoff, float* filterRes)
    {
        flt2_type = *filterType;
        flt2_cutoff = *filterCutoff;
        flt2_resonance = *filterRes;
    }
    
    //=================================================
    
    double getSummedOscillators()
    {
        double osc1 = env1.adsr(getOsc1Output(), env1.trigger) / 2.0f;
        double osc2 = env2.adsr(getOsc2Output(), env2.trigger) / 2.0f;
        
        return osc1 + osc2;
    }
    
    //=================================================
    
private:
    // VOICE INFO
    double level;
    double frequency;
    
    // OSCILLATORS
    int osc1_waveformType;
    maxiOsc osc1;
    int osc2_waveformType;
    maxiOsc osc2;
    
    // ENVELOPES
    maxiEnv env1;
    maxiEnv env2;
    
    // FILTER PARAMETERS
    // (NOTE: Filter is located outside of SynthVoice as a ProcessorDuplicator of type dsp::StateVariableFilter.)
    int flt1_type;
    float flt1_cutoff;
    float flt1_resonance;
    
    int flt2_type;
    float flt2_cutoff;
    float flt2_resonance;
};
