#include <JuceHeader.h>
#include "OscillatorView.h"

OscillatorView::OscillatorView(BasicsubtractivesynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    typeMenu.addItem("Sine", 1);
    typeMenu.addItem("Saw", 2);
    typeMenu.addItem("Square", 3);
    typeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&typeMenu);
}

OscillatorView::~OscillatorView()
{
}

void OscillatorView::paint (juce::Graphics& g)
{
    //background stuff
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator", titleArea, juce::Justification::centredTop);

    juce::Rectangle<float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorView::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    typeMenu.setBounds(area.removeFromTop(20));
}