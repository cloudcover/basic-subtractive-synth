#include <JuceHeader.h>
#include "MixerView.h"

MixerView::MixerView(BasicSubtractiveSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 400);
    
    osc1Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1Slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    osc1Slider.setRange(0.0f, 1.0f);
    osc1Slider.setValue(0.5f);
    osc1Slider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&osc1Slider);
    
    osc2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2Slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    osc2Slider.setRange(0.0f, 1.0f);
    osc2Slider.setValue(0.5f);
    osc2Slider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&osc2Slider);
    
    osc3Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc3Slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    osc3Slider.setRange(0.0f, 1.0f);
    osc3Slider.setValue(0.5f);
    osc3Slider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&osc3Slider);
}

MixerView::~MixerView() { }

void MixerView::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Mixer", titleArea, juce::Justification::centredTop);
    
    g.drawText("1", 50, 360, 20, 20, juce::Justification::centredTop);
    g.drawText("2", 90, 360, 20, 20, juce::Justification::centredTop);
    g.drawText("3", 130, 360, 20, 20, juce::Justification::centredTop);
    
    juce::Rectangle<float> area(25, 25, 150, 370);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void MixerView::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    int sliderWidth = 40;
    int sliderHeight = 320;
    
    osc1Slider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
    osc2Slider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
    osc3Slider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
}
