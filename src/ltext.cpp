#include "ltext.hpp"
#include "fontmetrics.hpp"

std::string_view ltext::resource_class() const {
  return "LTEXT";
}

YGSize ltext::measure([[maybe_unused]] YGNodeConstRef node, float width, [[maybe_unused]] YGMeasureMode width_mode, float height, YGMeasureMode height_mode) {
  if (height_mode != YGMeasureModeExactly)
    height = font_metrics::instance().dlu_to_dip_y(default_height_per_line_dlu); // FIXME assumes just one line

  return {width, height};
}
