#include "radiobutton.hpp"
#include "fontmetrics.hpp"

radiobutton::radiobutton(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, font_metrics::instance().dlu_to_dip_y(10));
}

std::string_view radiobutton::resource_class() const {
  return "RADIOBUTTON";
}
