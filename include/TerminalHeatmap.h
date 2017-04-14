#ifndef TERMINAL_HEATMAP_H
#define TERMINAL_HEATMAP_H

#include "Temperature.h"
#include "Color.h"

#include <vector>

template <typename T>
typedef Map<T> std::vector<std::vector<T>>;

class TerminalHeatmap
{
public:
  TerminalHeatmap(int height, int width);
  TerminalHeatmap(const Map<Temperature>& map);

  void setTemperature(unsigned int row, unsigned int col, Temperature temperature);
  void addOverlay(const ColorMap& overlay);
  void draw();
private:
  Map<Color> map_;
  std::vector<Map<Color>> overlays_;
}

#endif
