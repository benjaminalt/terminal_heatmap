#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <tuple>

class Color
{
public:
  Color(short red, short green, short blue);
  std::tuple<short, short, short> rgb();
private:
  short red_;
  short green_;
  short blue_;
};

#endif
