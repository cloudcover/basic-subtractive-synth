#include <JuceHeader.h>
#include "OscillatorView.h"

OscillatorView::OscillatorView(BasicSubtractiveSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    typeMenu.addItem("Sine", 1);
    typeMenu.addItem("Saw", 2);
    typeMenu.addItem("Square", 3);
    typeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&typeMenu);
    
    octaveMenu.addItem("-2", 1);
    octaveMenu.addItem("-1", 2);
    octaveMenu.addItem("0", 3);
    octaveMenu.addItem("+1", 4);
    octaveMenu.addItem("+2", 5);
    octaveMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&octaveMenu);
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
    g.drawText(overrideLabel, titleArea, juce::Justification::centredTop);

    // TODO: make these static positions dynamic
    g.drawText("Waveform", 0, 40, 200, 15, juce::Justification::centredTop);
    g.drawText("Octave", 0, 90, 200, 15, juce::Justification::centredTop);
    
    juce::Rectangle<float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorView::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    area.removeFromTop(20);
    typeMenu.setBounds(area.removeFromTop(20));
    area.removeFromTop(30);
    octaveMenu.setBounds(area.removeFromTop(20));
}
