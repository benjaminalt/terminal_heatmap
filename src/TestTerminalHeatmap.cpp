#include "TerminalHeatmap.h"

#include <unistd.h>

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
