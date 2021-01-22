#include "PluginProcessor.h"
#include "PluginEditor.h"

BasicSubtractiveSynthAudioProcessorEditor::BasicSubtractiveSynthAudioProcessorEditor (BasicSubtractiveSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Gui(p), osc2Gui(p), osc3Gui(p), mixerGui(p), envGui(p), fltGui(p)
{
    setSize (600, 600);
    
    // add the component instance bindings here instead of in the Component's constructor
    osc1Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC1_TYPE_ID, osc1Gui.typeMenu);
    osc1Gui.octaveMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC1_OCTAVE_ID, osc1Gui.octaveMenu);
    osc1Gui.overrideLabel = "Oscillator 1";
    addAndMakeVisible(&osc1Gui);
    
    osc2Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC2_TYPE_ID, osc2Gui.typeMenu);
    osc2Gui.octaveMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC2_OCTAVE_ID, osc2Gui.octaveMenu);
    osc2Gui.overrideLabel = "Oscillator 2";
    addAndMakeVisible(&osc2Gui);
    
    osc3Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC3_TYPE_ID, osc3Gui.typeMenu);
    osc3Gui.octaveMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC3_OCTAVE_ID, osc3Gui.octaveMenu);
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

    envGui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV_ATTACK_ID, envGui.attackSlider);
    envGui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV_DECAY_ID, envGui.decaySlider);
    envGui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV_SUSTAIN_ID, envGui.sustainSlider);
    envGui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV_RELEASE_ID, envGui.releaseSlider);
    addAndMakeVisible(&envGui);
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
    fltGui.setBounds(componentWidth * 2.0f, componentHeight / 2.0f, componentWidth, componentHeight);
    envGui.setBounds(componentWidth * 2.0f, componentHeight * 1.5f, componentWidth, componentHeight);
}
