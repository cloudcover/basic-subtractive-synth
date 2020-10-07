/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicsubtractivesynthAudioProcessorEditor::BasicsubtractivesynthAudioProcessorEditor (BasicsubtractivesynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Gui(p), osc2Gui(p), env1Gui(p), env2Gui(p), flt1Gui(p), flt2Gui(p)
{
    setSize (600, 400);

    // add the component instance bindings here instead of in the Component's constructor
    osc1Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC1_TYPE_ID, osc1Gui.typeMenu);
    addAndMakeVisible(&osc1Gui);
    
    osc2Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, OSC2_TYPE_ID, osc2Gui.typeMenu);
    addAndMakeVisible(&osc2Gui);

    env1Gui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_ATTACK_ID, env1Gui.attackSlider);
    env1Gui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_DECAY_ID, env1Gui.decaySlider);
    env1Gui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_SUSTAIN_ID, env1Gui.sustainSlider);
    env1Gui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_RELEASE_ID, env1Gui.releaseSlider);
    addAndMakeVisible(&env1Gui);

    env2Gui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV2_ATTACK_ID, env2Gui.attackSlider);
    env2Gui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV2_DECAY_ID, env2Gui.decaySlider);
    env2Gui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV2_SUSTAIN_ID, env2Gui.sustainSlider);
    env2Gui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV2_RELEASE_ID, env2Gui.releaseSlider);
    addAndMakeVisible(&env2Gui);

    flt1Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, FLT1_TYPE_ID, flt1Gui.typeMenu);
    flt1Gui.cutoffSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT1_CUTOFF_ID, flt1Gui.cutoffSlider);
    flt1Gui.resonanceSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT1_RESONANCE_ID, flt1Gui.resonanceSlider);
    addAndMakeVisible(&flt1Gui);

    flt2Gui.typeMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, FLT2_TYPE_ID, flt2Gui.typeMenu);
    flt2Gui.cutoffSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT2_CUTOFF_ID, flt2Gui.cutoffSlider);
    flt2Gui.resonanceSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, FLT2_RESONANCE_ID, flt2Gui.resonanceSlider);
    addAndMakeVisible(&flt2Gui);
}

BasicsubtractivesynthAudioProcessorEditor::~BasicsubtractivesynthAudioProcessorEditor()
{
}

//==============================================================================
void BasicsubtractivesynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void BasicsubtractivesynthAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    osc1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    env1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    flt1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    osc2Gui.setBounds(0.0f, componentHeight, componentWidth, componentHeight);
    env2Gui.setBounds(componentWidth, componentHeight, componentWidth, componentHeight);
    flt2Gui.setBounds(componentWidth * 2.0f, componentHeight, componentWidth, componentHeight);
}
