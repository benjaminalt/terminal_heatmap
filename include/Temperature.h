#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Color.h"

class Temperature
{
public:
  static Temperature fromPercent(double percent);
  // static Temperature fromCelsius(double celsius);
  // static Temperature fromFahrenheit(double fahrenheit);
  Color color();
  unsigned int value();
  static const unsigned int maxValue_ = 4 * 1000;
  static const unsigned int minValue_ = 0;

private:
  Temperature(unsigned int value);
  unsigned int value_;
};

#endif
