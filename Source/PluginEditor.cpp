#include "PluginProcessor.h"
#include "PluginEditor.h"

BasicsubtractivesynthAudioProcessorEditor::BasicsubtractivesynthAudioProcessorEditor (BasicsubtractivesynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Gui(p), osc2Gui(p), osc3Gui(p), fltGui(p), fltEnvGui(p), ampEnvGui(p)
{
    setSize (600, 400);

    // TODO: create a MixerView and bind it here
    
    // add the component instance bindings here instead of in the Component's constructor
    osc1Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC1_TYPE_ID, osc1Gui.typeMenu);
    addAndMakeVisible(&osc1Gui);
    osc2Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC2_TYPE_ID, osc2Gui.typeMenu);
    addAndMakeVisible(&osc2Gui);
    osc3Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC3_TYPE_ID, osc3Gui.typeMenu);
    addAndMakeVisible(&osc3Gui);
    
    fltGui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, FLT_TYPE_ID, fltGui.typeMenu);
    fltGui.cutoffSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_CUTOFF_ID, fltGui.cutoffSlider);
    fltGui.resonanceSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_RESONANCE_ID, fltGui.resonanceSlider);
    addAndMakeVisible(&fltGui);

    fltEnvGui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_ATTACK_ID, fltEnvGui.attackSlider);
    fltEnvGui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_DECAY_ID, fltEnvGui.decaySlider);
    fltEnvGui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_SUSTAIN_ID, fltEnvGui.sustainSlider);
    fltEnvGui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT_ENV_RELEASE_ID, fltEnvGui.releaseSlider);
    addAndMakeVisible(&fltEnvGui);

    ampEnvGui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_ATTACK_ID, ampEnvGui.attackSlider);
    ampEnvGui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_DECAY_ID, ampEnvGui.decaySlider);
    ampEnvGui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_SUSTAIN_ID, ampEnvGui.sustainSlider);
    ampEnvGui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, AMP_ENV_RELEASE_ID, ampEnvGui.releaseSlider);
    addAndMakeVisible(&ampEnvGui);
}

BasicsubtractivesynthAudioProcessorEditor::~BasicsubtractivesynthAudioProcessorEditor()
{
}

void BasicsubtractivesynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void BasicsubtractivesynthAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    // TODO: 1) add osc3Gui, 2) re-arrange everything in classic Moog layout.
    
    osc1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    fltEnvGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    fltGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    osc2Gui.setBounds(0.0f, componentHeight, componentWidth, componentHeight);
    ampEnvGui.setBounds(componentWidth, componentHeight, componentWidth, componentHeight);
}
