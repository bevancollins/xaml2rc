#include "edittext.hpp"
#include <format>
#include "fontmetrics.hpp"

std::string_view edittext::resource_class() const {
  return "EDITTEXT";
}

void edittext::output(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} {}, {}, {}, {}, {}", resource_class(), id_, x(node), y(node), width(node), height(node));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

YGSize edittext::measure([[maybe_unused]] YGNodeConstRef node, float width, [[maybe_unused]] YGMeasureMode width_mode, float height, YGMeasureMode height_mode) {
  if (height_mode != YGMeasureModeExactly)
    height = font_metrics::instance().dlu_to_dip_y(default_height_dlu);

  return {width, height};
}
