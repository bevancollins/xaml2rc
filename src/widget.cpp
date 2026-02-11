#include "widget.hpp"
#include <algorithm>
#include "fontmetrics.hpp"

void widget::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::process_xaml(xaml, node);

  auto is_tab_stop = xaml.attribute("IsTabStop").as_bool(true);
  if (is_tab_stop)
    style_.push_back("WS_TABSTOP");
}

void widget::measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) {
  resource::measure(node, width, width_mode, height, height_mode);

  if (height_mode != YGMeasureModeExactly) {
    float default_height_dip = font_metrics::instance().dlu_to_dip_y(default_height_dlu());
    if (height_mode == YGMeasureModeAtMost)
      height = std::min(height, default_height_dip);
    else
      height = default_height_dip;

    height_mode = YGMeasureModeExactly;
  }
}

int widget::default_height_dlu() const {
  return 14;
}
