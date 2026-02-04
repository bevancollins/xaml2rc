#include "pushbutton.hpp"
#include "fontmetrics.hpp"

std::string_view pushbutton::resource_class() const {
  return "PUSHBUTTON";
}

void pushbutton::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  common_text_control::from_xaml(xaml, node);

  auto is_default = xaml.attribute("IsDefault");
  if (is_default.as_bool() && id_.empty())
    id_ = "IDOK";

  auto is_cancel = xaml.attribute("IsCancel");
  if (is_cancel.as_bool() && id_.empty())
    id_ = "IDCANCEL";
}

YGSize pushbutton::measure(float width, YGMeasureMode width_mode, float height, YGMeasureMode height_mode) {
  if (width_mode != YGMeasureModeExactly)
    width = font_metrics::instance().dlu_to_dip_x(default_width_dlu);

  if (height_mode != YGMeasureModeExactly)
    height = font_metrics::instance().dlu_to_dip_y(default_height_dlu);

  return {width, height};
}
