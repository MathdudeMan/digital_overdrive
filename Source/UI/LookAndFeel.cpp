/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 30 Dec 2025 3:52:03pm
    Author:  mathd

  ==============================================================================
*/

#include "LookAndFeel.h"

// ==============================================================================
// CircleLookAndFeel definitions

void CircleLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto diameter = (float)jmin(width, height); 
    auto radius = (diameter / 2.0f) * std::cos(MathConstants<float>::pi / 4.0f);
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    auto baseColour = slider.isEnabled() ? slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 0.8f : 1.0f)
        : Colour(0x80808080);

    Rectangle<float> r(rx, ry, rw, rw);
    auto transform = AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY());

    auto x1 = r.getTopLeft().getX();
    auto y1 = r.getTopLeft().getY();
    auto x2 = r.getBottomLeft().getX();
    auto y2 = r.getBottomLeft().getY();

    transform.transformPoints(x1, y1, x2, y2);

    g.setGradientFill(ColourGradient(baseColour, x1, y1,
        baseColour.darker(0.1f), x2, y2,
        false));

    Path knob;
    knob.addEllipse(r);
    g.fillPath(knob, transform);

    Path needle;
    auto r2 = r * 0.1f;
    needle.addRectangle(r2.withPosition({ r.getCentreX() - (r2.getWidth() / 2.0f), r.getY() }));

    g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId));
    g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
}
