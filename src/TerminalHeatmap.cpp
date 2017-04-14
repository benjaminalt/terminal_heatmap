#include "TerminalHeatmap.h"

#include <stdexcept>

TerminalHeatmap::TerminalHeatmap(int height, int width)
{
  map_ = std::vector<std::vector<Color>>(height, std::vector<Color>(width, Color::fromPercent(0)));
}

TerminalHeatmap::TerminalHeatmap(const Map<Temperature>& map)
{
  for (int i = 0; i < map.size(); i++)
  {
    std::vector<Color> row = map[i];
    map_.push_back(std::vector<Color>());
    for (Temperature cell : row)
    {
      map_[i].push_back(cell.color());
    }
  }
}

void TerminalHeatmap::setTemperature(unsigned int row, unsigned int col, Temperature temperature)
{
  if (map.size() == 0)
  {
    throw std::runtime_error("Cannot set temperature: Map empty");
  }
  if (row < 0 || row >= map_.size())
  {
    throw std::range_error("Row out of range");
  }
  if (col < 0 || col >= map[0].size())
  {
    throw std::range_error("Column out of range");
  }
  map_[row][col] = temperature.color();
}

void TerminalHeatmap::addOverlay(const ColorMap& overlay)
{
  overlays_.push_back(overlay);
}

int main(int argc, char* argv[])
{
  return 0;
}
