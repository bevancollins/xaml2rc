#include "common_text_control.hpp"
#include <algorithm>
#include <format>
#include "fontmetrics.hpp"

void common_text_control::to_rc(YGNodeConstRef node, std::ostream& os) const {
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

YGNodeRef common_text_control::from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = resource::from_xaml(xaml, parent);

  auto content = xaml.attribute("Content");
  if (content)
    text_ = content.value();

  auto is_tab_stop = xaml.attribute("IsTabStop").as_bool(true);
  if (is_tab_stop)
    style_.push_back("WS_TABSTOP");

  return node;
}

int common_text_control::default_height_dlu() const {
  return 14;
}

void common_text_control::measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) {
  // Calculate intrinsic width based on text
  if (width_mode != YGMeasureModeExactly) {
    float text_width = font_metrics::instance().measure_text_width_dip(text_);
    if (width_mode == YGMeasureModeAtMost)
      width = std::min(width, text_width);
    else
      width = text_width;

    width_mode = YGMeasureModeExactly;
  }

  if (height_mode != YGMeasureModeExactly) {
    float default_height_dip = font_metrics::instance().dlu_to_dip_y(default_height_dlu());
    if (height_mode == YGMeasureModeAtMost)
      height = std::min(height, default_height_dip);
    else
      height = default_height_dip;

    height_mode = YGMeasureModeExactly;
  }
}
