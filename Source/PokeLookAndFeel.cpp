#include "PokeLookAndFeel.h"

PokeLookAndFeel::PokeLookAndFeel() {
  setColour(Slider::backgroundColourId, Colour(0xffe1e1e1));
  setColour(Slider::thumbColourId, Colour(0xffeb008b));
}

void PokeLookAndFeel::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height,
                                            float sliderPos, float minSliderPos, float maxSliderPos,
                                            const Slider::SliderStyle style, Slider &slider) {
    const float radius = getSliderThumbRadius(slider);

    g.setColour(slider.findColour(Slider::thumbColourId));

    float kx, ky;

    if (style == Slider::LinearVertical) {
      kx = x + width * 0.5f;
      ky = sliderPos;
    } else {
      kx = sliderPos;
      ky = y + height * 0.5f;
    }

    Path circle;
    circle.addCentredArc(kx, ky, radius, radius, 0.0f, 0.0f, M_PI * 2.0f);

    g.fillPath(circle);
}

void PokeLookAndFeel::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height,
                                                 float sliderPos, float minSliderPos,
                                                 float maxSliderPos,
                                                 const Slider::SliderStyle style, Slider &slider) {
  const float radius = std::floor(getSliderThumbRadius(slider) * 0.333f);

  g.setColour(slider.findColour(Slider::backgroundColourId));

  Path indent;

  if (slider.isHorizontal()) {
    const float iy = y + height * 0.5f - radius;
    indent.addRoundedRectangle(x - radius, iy, width + radius, radius * 2.0f, radius);
  } else {
    const float ix = x + width * 0.5f - radius;
    indent.addRoundedRectangle(ix, y - radius, radius * 2.0f, height + radius, radius);
  }

  g.fillPath(indent);
}

void PokeLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height,
                                       float sliderPos, float minSliderPos, float maxSliderPos,
                                       const Slider::SliderStyle style, Slider &slider) {
  drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style,
                             slider);
  drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style,
                        slider);
}

int PokeLookAndFeel::getSliderThumbRadius(Slider &slider) {
  return jmin(10, slider.getHeight() / 2, slider.getWidth() / 2);
}
