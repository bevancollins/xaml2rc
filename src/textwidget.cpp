#include "textwidget.hpp"
#include <algorithm>
#include <format>
#include "fontmetrics.hpp"

void text_widget::output(std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), text_, id_, x(), y(), width(), height());

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

void text_widget::process_xaml(const pugi::xml_node& xaml) {
  widget::process_xaml(xaml);

  auto content = xaml.attribute("Content");
  if (content)
    text_ = content.value();
}

void text_widget::measure(float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) {
  widget::measure(width, width_mode, height, height_mode);

  // Calculate intrinsic width based on text
  if (width_mode != YGMeasureModeExactly) {
    float text_width = font_metrics::instance().measure_text_width_dip(text_);
    if (width_mode == YGMeasureModeAtMost)
      width = std::min(width, text_width);
    else
      width = text_width;

    width_mode = YGMeasureModeExactly;
  }
}
