#include <JuceHeader.h>
#include "FilterView.h"

FilterView::FilterView(BasicSubtractiveSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);
    typeMenu.addItem("Low Pass", 1);
    typeMenu.addItem("High Pass", 2);
    typeMenu.addItem("Band Pass", 3);
    typeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&typeMenu);

    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setRange(20.0f, 10000.0f);
    cutoffSlider.setValue(400.0f);
    cutoffSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    cutoffSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&cutoffSlider);

    resonanceSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSlider.setRange(1.0f, 5.0f);
    resonanceSlider.setValue(1.0f);
    resonanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    resonanceSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&resonanceSlider);
}

FilterView::~FilterView()
{
}

void FilterView::paint (juce::Graphics& g)
{
    //background ui stuff
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
    
    // TODO: Draw these in an anchored way instead of static so they resize on window drag properly
    g.drawText("Type", 75, 38, 50, 20, juce::Justification::centredTop);
    g.drawText("Cutoff", 40, 88, 50, 20, juce::Justification::centredTop);
    g.drawText("Resonance", 100, 88, 70, 20, juce::Justification::centredTop);

    juce::Rectangle<float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterView::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    area.removeFromTop(15);
    typeMenu.setBounds(area.removeFromTop(20));
    cutoffSlider.setBounds(30, 100, 70, 70);
    resonanceSlider.setBounds(100, 100, 70, 70);

}
