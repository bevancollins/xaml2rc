#include "edittext.hpp"
#include "fontmetrics.hpp"

edittext::edittext(YGNodeRef node) :
  widget(node) {
  YGNodeStyleSetHeight(node_, font_metrics::instance().dlu_to_dip_y(14));
}

std::string_view edittext::resource_class() const {
  return "EDITTEXT";
}
