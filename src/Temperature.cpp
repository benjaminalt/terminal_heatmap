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
  unsigned int value = Temperature::minValue_ + (unsigned int)((Temperature::maxValue_ - Temperature::minValue_) * (percent / 100.0));
  return Temperature(value);
}

unsigned int Temperature::value()
{
  return value_;
}

Color Temperature::color()
{
  if (value_ <= 1000)
  {
    return Color(1000, value_, 0);
  }
  else if (value_ <= 2 * 1000)
  {
    unsigned int remainder = value_ - 1000;
    return Color(1000 - remainder, 1000, 0);
  }
  else if (value_ <= 3 * 1000)
  {
    unsigned int remainder = value_ - 2 * 1000;
    return Color(0, 1000, remainder);
  }
  else if (value_ <= 4 * 1000)
  {
    unsigned int remainder = value_ - 3 * 1000;
    return Color(0, 1000 - remainder, 1000);
  }
  else
  {
    throw std::range_error("Temperature internal value out of range: " + std::to_string(value_));
  }
}
