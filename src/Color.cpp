#include "Color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
  red_ = red;
  green_ = green;
  blue_ = blue;
}

std::tuple<uint8_t, uint8_t, uint8_t> Color::rgb()
{
  return std::tuple<uint8_t, uint8_t, uint8_t>(red_, green_, blue_);
}
