#include "Temperature.h"

#include <stdexcept>

Temperature::Temperature(unsigned int value)
{
  value_ = value;
}

Temperature Temperature::fromPercent(double percent)
{
  if (percent < 0 || percent > 100)
  {
    throw std::invalid_argument("Percentage out of range: Must be between 0 and 100");
  }
  unsigned int value = Temperature::maxValue_ - (unsigned int)((Temperature::maxValue_ - Temperature::minValue_) * (percent / 100.0));
  return Temperature(value);
}

Color Temperature::color()
{
  if (value_ <= 255)
  {
    return Color(255, value_, 0);
  }
  else if (value_ <= 2 * 255)
  {
    unsigned int remainder = value_ - 255;
    return Color(255 - remainder, 255, 0);
  }
  else if (value_ <= 3 * 255)
  {
    unsigned int remainder = value_ - 2 * 255;
    return Color(0, 255, remainder);
  }
  else if (value_ <= 4 * 255)
  {
    unsigned int remainder = value_ - 3 * 255;
    return Color(0, 255 - remainder, 255);
  }
  else
  {
    throw std::range_error("Temperature internal value out of range: " + std::to_string(value_));
  }
}
