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
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        ampEnv.trigger = 1;
        
        // TODO: make actual use of the incoming velocity value.
        
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff)
    {
        ampEnv.trigger = 0;
        
        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }

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
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        // no implementation yet
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        // no implementation yet
    }
    
    // ================ other functions ================
    void setOsc1Type(float* selection)
    {
        osc1_waveformType = *selection;
    }
    
    void setOsc2Type(float* selection)
    {
        osc2_waveformType = *selection;
    }
    
    void setOsc3Type(float* selection)
    {
        osc3_waveformType = *selection;
    }
    
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
    
    double getOsc3Output()
    {
        switch (osc3_waveformType)
        {
            case 0: return osc3.sinewave(frequency);
            case 1: return osc3.saw(frequency);
            case 2: return osc3.square(frequency);
        }
        
        return osc3.sinewave(frequency);
    }
    
    void setOsc1OctaveOffset(int* offset)
    {
        osc1_octaveOffset = *offset;
    }
    
    void setOsc2OctaveOffset(int* offset)
    {
        osc2_octaveOffset = *offset;
    }
    
    void setOsc3OctaveOffset(int* offset)
    {
        osc3_octaveOffset = *offset;
    }
    
    void setEnvParams(float* attack, float* decay, float* sustain, float* release)
    {
        ampEnv.setAttack(double(*attack));
        ampEnv.setDecay(double(*decay));
        ampEnv.setSustain(double(*sustain));
        ampEnv.setRelease(double(*release));
    }
    
    void setFltParams(float* filterType, float* filterCutoff, float* filterRes)
    {
        fltType = *filterType;
        fltCutoff = *filterCutoff;
        fltResonance = *filterRes;
    }
    
    void setOscLevels(float* osc1Level, float* osc2Level, float* osc3Level)
    {
        osc1_level = *osc1Level;
        osc2_level = *osc2Level;
        osc3_level = *osc3Level;
    }
    
    double getSummedOscillators()
    {
        double osc1 = ampEnv.adsr(getOsc1Output(), ampEnv.trigger) / 3.0f * osc1_level;
        double osc2 = ampEnv.adsr(getOsc2Output(), ampEnv.trigger) / 3.0f * osc2_level;
        double osc3 = ampEnv.adsr(getOsc3Output(), ampEnv.trigger) / 3.0f * osc3_level;
        
        return osc1 + osc2 + osc3;
    }
    
private:
    // VOICE INFO
    double frequency;
    
    // OSCILLATORS
    int osc1_waveformType;
    float osc1_level;
    int osc1_octaveOffset;
    maxiOsc osc1;
    
    int osc2_waveformType;
    float osc2_level;
    int osc2_octaveOffset;
    maxiOsc osc2;
    
    int osc3_waveformType;
    float osc3_level;
    int osc3_octaveOffset;
    maxiOsc osc3;
    
    // ENVELOPES
    maxiEnv ampEnv;
    
    // FILTER PARAMETERS
    // (NOTE: Filter is located outside of SynthVoice as a ProcessorDuplicator of type dsp::StateVariableFilter.)
    int fltType;
    float fltCutoff;
    float fltResonance;
};
