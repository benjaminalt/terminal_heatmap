#include "Color.h"

Color::Color(short red, short green, short blue)
{
  red_ = red;
  green_ = green;
  blue_ = blue;
}

std::tuple<short, short, short> Color::rgb()
{
  return std::tuple<short, short, short>(red_, green_, blue_);
}
