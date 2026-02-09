#include "checkbox.hpp"
#include "fontmetrics.hpp"

std::string_view checkbox::resource_class() const {
  return "CHECKBOX";
}

YGSize checkbox::measure([[maybe_unused]] YGNodeConstRef node, float width, YGMeasureMode width_mode, float height, YGMeasureMode height_mode) {
  if (height_mode != YGMeasureModeExactly)
    height = font_metrics::instance().dlu_to_dip_y(default_height_dlu);

  return {width, height};
}
