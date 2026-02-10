#include "textwidget.hpp"
#include <algorithm>
#include <format>
#include "fontmetrics.hpp"

void text_widget::to_rc(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), text_, id_, x(node), y(node), width(node), height(node));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

YGNodeRef text_widget::from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = widget::from_xaml(xaml, parent);

  auto content = xaml.attribute("Content");
  if (content)
    text_ = content.value();

  return node;
}

void text_widget::measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) {
  widget::measure(node, width, width_mode, height, height_mode);

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
