#include "PluginProcessor.h"
#include "PluginEditor.h"

BasicSubtractiveSynthAudioProcessorEditor::BasicSubtractiveSynthAudioProcessorEditor (BasicSubtractiveSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Gui(p), osc2Gui(p), osc3Gui(p), fltGui(p), fltEnvGui(p), ampEnvGui(p), mixerGui(p)
{
    setSize (1000, 600);
    
    // add the component instance bindings here instead of in the Component's constructor
    osc1Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC1_TYPE_ID, osc1Gui.typeMenu);
    osc1Gui.overrideLabel = "Oscillator 1";
    addAndMakeVisible(&osc1Gui);
    osc2Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC2_TYPE_ID, osc2Gui.typeMenu);
    osc2Gui.overrideLabel = "Oscillator 2";
    addAndMakeVisible(&osc2Gui);
    osc3Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC3_TYPE_ID, osc3Gui.typeMenu);
    osc3Gui.overrideLabel = "Oscillator 3";
    addAndMakeVisible(&osc3Gui);
    
    mixerGui.osc1SliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, OSC1_LEVEL_ID, mixerGui.osc1Slider);
    mixerGui.osc2SliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, OSC2_LEVEL_ID, mixerGui.osc2Slider);
    mixerGui.osc3SliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, OSC3_LEVEL_ID, mixerGui.osc3Slider);
    addAndMakeVisible(&mixerGui);
    
    fltGui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, FLT_TYPE_ID, fltGui.typeMenu);
    fltGui.cutoffSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_CUTOFF_ID, fltGui.cutoffSlider);
    fltGui.resonanceSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_RESONANCE_ID, fltGui.resonanceSlider);
    addAndMakeVisible(&fltGui);

    fltEnvGui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_ATTACK_ID, fltEnvGui.attackSlider);
    fltEnvGui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_DECAY_ID, fltEnvGui.decaySlider);
    fltEnvGui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_SUSTAIN_ID, fltEnvGui.sustainSlider);
    fltEnvGui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_RELEASE_ID, fltEnvGui.releaseSlider);
    fltEnvGui.overrideLabel = "Filter Envelope";
    addAndMakeVisible(&fltEnvGui);

    ampEnvGui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_ATTACK_ID, ampEnvGui.attackSlider);
    ampEnvGui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_DECAY_ID, ampEnvGui.decaySlider);
    ampEnvGui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_SUSTAIN_ID, ampEnvGui.sustainSlider);
    ampEnvGui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_RELEASE_ID, ampEnvGui.releaseSlider);
    ampEnvGui.overrideLabel = "Amplitude Envelope";
    addAndMakeVisible(&ampEnvGui);
}

BasicSubtractiveSynthAudioProcessorEditor::~BasicSubtractiveSynthAudioProcessorEditor() { }

void BasicSubtractiveSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void BasicSubtractiveSynthAudioProcessorEditor::resized()
{
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    osc1Gui.setBounds(0.0f, 0.0f, componentWidth, componentHeight);
    osc2Gui.setBounds(0.0f, componentHeight, componentWidth, componentHeight);
    osc3Gui.setBounds(0.0f, componentHeight * 2.0f, componentWidth, componentHeight);
    mixerGui.setBounds(componentWidth, 100.0f, componentWidth, componentHeight * 2.0f);
    fltEnvGui.setBounds(componentWidth * 2.0f, componentHeight, componentWidth, componentHeight);
    ampEnvGui.setBounds(componentWidth * 3.0f, componentHeight, componentWidth, componentHeight);
    fltGui.setBounds(componentWidth * 4.0f, componentHeight, componentWidth, componentHeight);
}
