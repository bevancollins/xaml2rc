#include "checkbox.hpp"
#include "fontmetrics.hpp"

checkbox::checkbox(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, font_metrics::instance().dlu_to_dip_y(10));
}

std::string_view checkbox::resource_class() const {
  return "CHECKBOX";
}
