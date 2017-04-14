#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Color.h"

class Temperature
{
public:
  static Temperature fromPercent(double percent);
  // static Temperature fromCelsius(double celsius);
  // static Temperature fromFahrenheit(double fahrenheit);
  /**
  *
  */
  Color color();
private:
  Temperature(unsigned int value);
  unsigned int value_;
  static const unsigned int maxValue_ = 4 * 255;
  static const unsigned int minValue_ = 0;
}

#endif
