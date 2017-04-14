#ifndef TERMINAL_HEATMAP_H
#define TERMINAL_HEATMAP_H

#include "Temperature.h"
#include "Color.h"

#include <ncurses.h>
#include <vector>

template <typename T>
using Map = typename std::vector<std::vector<T>>;

class TerminalHeatmap
{
public:
  /**
  * \brief Construct an empty TerminalHeatmap with a given height and width.
  * All cells are initialized to RGB(0,0,0) (black).
  */
  TerminalHeatmap(int height, int width);

  /**
  * \brief Construct a TerminalHeatmap from a temperature map.
  * Assumption: All rows in the map have the same length.
  */
  TerminalHeatmap(const Map<Temperature>& map);

  /**
  * \brief Destroys the TerminalHeatmap.
  * Restores terminal settings.
  */
  ~TerminalHeatmap();

  void setTemperature(unsigned int row, unsigned int col, Temperature temperature);

  /**
  * \brief Applies an overlay (colors pixels in the heatmap white where the overlay cell contains TRUE).
  * Overlays are applied like a stack --> those added later are applied over those added before.
  * Assumption: Overlay has same dimensions as map.
  */
  void addOverlay(const Map<bool>& overlay);

  /**
  * \brief Sets the overlay at the given index.
  * Assumption: Overlay already exists (if not, call addOverlay instead).
  */
  void setOverlay(size_t overlayIndex, const Map<bool>& overlay);
  void redraw();
private:
  void initScreen();

  Map<Temperature> map_;
  std::vector<Map<bool>> overlays_;
  WINDOW* win_;
  std::vector<Color> oldColors_;
  std::vector<std::tuple<short,short>> oldPairs_;
};

#endif
