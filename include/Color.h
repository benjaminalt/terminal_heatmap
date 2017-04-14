#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <tuple>

class Color
{
public:
  Color(uint8_t red, uint8_t green, uint8_t blue);
  std::tuple<uint8_t, uint8_t, uint8_t> rgb();
private:
  uint8_t red_;
  uint8_t green_;
  uint8_t blue_;
}

#endif
