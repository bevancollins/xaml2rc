#include "ltext.hpp"
#include "fontmetrics.hpp"

ltext::ltext(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, font_metrics::instance().dlu_to_dip_y(8));
}

std::string_view ltext::resource_class() const {
  return "LTEXT";
}
