#include "TerminalHeatmap.h"

#include <stdexcept>
#include <cmath>
#include <unistd.h>

TerminalHeatmap::TerminalHeatmap(int height, int width)
{
  if (height <= 0 || width <= 0)
  {
    throw std::invalid_argument("Map width and height must be positive");
  }
  map_ = std::vector<std::vector<Temperature>>(height, std::vector<Temperature>(width, Temperature::fromPercent(0)));
  initScreen();
}

TerminalHeatmap::TerminalHeatmap(const Map<Temperature>& map)
{
  if (map.size() == 0 || map[0].size() == 0)
  {
    throw std::invalid_argument("Map width and height must be positive");
  }
  for (int i = 0; i < map.size(); i++)
  {
    std::vector<Temperature> row = map[i];
    map_.push_back(std::vector<Temperature>());
    for (Temperature cell : row)
    {
      map_[i].push_back(cell);
    }
  }
  initScreen();
}

TerminalHeatmap::~TerminalHeatmap()
{
  delwin(win_);
  restoreColorSpace();
  endwin(); // Restore terminal settings
}

void TerminalHeatmap::initScreen()
{
  initscr();
  noecho();
  start_color();
  int nlines = map_.size();
  int ncols = map_[0].size() * 2;
  if (nlines > LINES || ncols > COLS)
  {
    throw std::runtime_error("Cannot draw map: Window too small");
  }
  win_ = newwin(nlines, ncols, 0, 0);

  saveColorSpace();

  // Initialize the color space based on the available colors
  // White is reserved (color at index 0)
  init_color(WHITE, 1000, 1000, 1000);
  init_pair(WHITE, WHITE, WHITE);
  init_color(BLACK, 0, 0, 0);
  init_pair(BLACK, BLACK, BLACK);
  // Rest of the color space is distributed equally among all possible temperatures
  for (int i = 0; i < COLORS - 2; i++)
  {
    Temperature temp = Temperature::fromPercent(((double)i / (double)(COLORS - 2))* 100);
    Color col = temp.color();
    std::tuple<int, int, int> tpl = col.rgb();
    int red = std::get<0>(tpl);
    int green = std::get<1>(tpl);
    int blue = std::get<2>(tpl);
    init_color(i + 2, red, green, blue);
    init_pair(i + 2, i + 2, WHITE);
  }
}

void TerminalHeatmap::saveColorSpace()
{
  for (int i = 0; i < COLORS; i++)
  {
    short r, g, b;
    color_content(i, &r, &g, &b);
    oldColors_.push_back(Color(r, g, b));
  }
  for (int i = 0; i < COLOR_PAIRS; i++)
  {
    short f, b;
    pair_content(i, &f, &b);
    oldPairs_.push_back(std::tuple<short,short>(f, b));
  }
}

void TerminalHeatmap::restoreColorSpace()
{
  for (int i = 0; i < oldColors_.size(); i++)
  {
    std::tuple<int,int,int> tpl = oldColors_[i].rgb();
    init_color(i, std::get<0>(tpl), std::get<1>(tpl), std::get<2>(tpl));
  }
  // Restore old color pairs
  for (int i = 0; i < oldPairs_.size(); i++)
  {
    std::tuple<short, short> tpl = oldPairs_[i];
    init_pair(i, std::get<0>(tpl), std::get<1>(tpl));
  }
}

void TerminalHeatmap::setTemperature(unsigned int row, unsigned int col, Temperature temperature)
{
  if (map_.size() == 0)
  {
    throw std::runtime_error("Cannot set temperature: Map empty");
  }
  if (row < 0 || row >= map_.size())
  {
    throw std::range_error("Row out of range");
  }
  if (col < 0 || col >= map_[0].size())
  {
    throw std::range_error("Column out of range");
  }
  map_[row][col] = temperature;
}

void TerminalHeatmap::addOverlay(const Map<bool>& overlay)
{
  overlays_.push_back(overlay);
}

void TerminalHeatmap::setOverlay(size_t overlayIndex, const Map<bool>& overlay)
{
  if (overlayIndex < 0 || overlayIndex >= overlays_.size())
  {
    throw std::range_error("Overlay index out of range");
  }
  overlays_[overlayIndex] = overlay;
}

void TerminalHeatmap::redraw()
{
  if (!win_)
  {
    throw std::runtime_error("Cannot redraw map: Window is null");
  }
  wmove(win_, 0, 0);
  int temperatureInterval = (Temperature::maxValue_ - Temperature::minValue_) / (COLORS - 2);
  for (int i = 0; i < map_.size(); i++)
  {
    for (int j = 0; j < map_[i].size(); j++)
    {
      // Which color in the color space is closest?
      int colorIndex = std::round((double) map_[i][j].value() / (double) temperatureInterval) + 2;
      wattron(win_, COLOR_PAIR(colorIndex));

      // Apply overlays
      for (Map<bool> overlay : overlays_)
      {
        if (overlay[i][j])
        {
          wattron(win_, COLOR_PAIR(BLACK));
        }
      }
      waddch(win_, ' ' | A_REVERSE); // Print a block in that color
      waddch(win_, ' ' | A_REVERSE); // Print a block in that color (to make it look square
    }
  }
  wrefresh(win_);
}

int main(int argc, char* argv[])
{
  TerminalHeatmap heatmap = TerminalHeatmap(10, 10);
  Map<bool> overlay;
  for (int i = 0; i < 10; i++)
  {
    overlay.push_back(std::vector<bool>());
    for (int j = 0; j < 10; j++)
    {
      heatmap.setTemperature(i, j, Temperature::fromPercent(i * 10));
      overlay[i].push_back(j == 0);
    }
  }
  heatmap.addOverlay(overlay);
  heatmap.redraw();
  sleep(2);
}
