cmake_minimum_required (VERSION 2.8.11)
project (terminal_heatmap)

include_directories(include)
add_executable(test_heatmap src/TerminalHeatmap.cpp src/Color.cpp src/Temperature.cpp)
target_compile_features(test_heatmap PRIVATE cxx_range_for)
