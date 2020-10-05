/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicsubtractivesynthAudioProcessorEditor::BasicsubtractivesynthAudioProcessorEditor (BasicsubtractivesynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), env1Gui(p)
{
    setSize (600, 400);

    // add the component instance bindings here instead of in the Component's constructor
    env1Gui.attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_ATTACK_ID, env1Gui.attackSlider);
    env1Gui.decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_DECAY_ID, env1Gui.decaySlider);
    env1Gui.sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_SUSTAIN_ID, env1Gui.sustainSlider);
    env1Gui.releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, ENV1_RELEASE_ID, env1Gui.releaseSlider);
    addAndMakeVisible(&env1Gui);
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

    env1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
