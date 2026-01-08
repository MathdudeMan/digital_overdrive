/*
  ==============================================================================

    LookAndFeel.h
    Created: 30 Dec 2025 3:52:03pm
    Author:  mathd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

// ==============================================================================
/**
    A look and feel with circular knobs.
*/
struct CircleLookAndFeel final : public LookAndFeel_V4
{
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
};