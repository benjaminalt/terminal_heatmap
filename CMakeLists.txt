cmake_minimum_required (VERSION 2.8.11)
project (terminal_heatmap)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(
  include
  ${Curses_INCLUDE_DIR}
)

add_library(terminal_heatmap src/TerminalHeatmap.cpp src/Temperature.cpp src/Color.cpp)
target_compile_features(terminal_heatmap PRIVATE cxx_range_for)
target_link_libraries(terminal_heatmap ncurses)

add_executable(test_heatmap src/TestTerminalHeatmap.cpp)
target_compile_features(test_heatmap PRIVATE cxx_range_for)
target_link_libraries(test_heatmap terminal_heatmap)
