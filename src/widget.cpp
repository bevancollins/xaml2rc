#include "widget.hpp"
#include <algorithm>
#include "fontmetrics.hpp"

void widget::process_xaml(const pugi::xml_node& xaml) {
  resource::process_xaml(xaml);

  auto is_tab_stop = xaml.attribute("IsTabStop").as_bool(true);
  if (is_tab_stop)
    style_.push_back("WS_TABSTOP");

  YGNodeStyleSetHeight(node_, font_metrics::instance().dlu_to_dip_y(default_height_dlu()));
}

int widget::default_height_dlu() const {
  return 14;
}
