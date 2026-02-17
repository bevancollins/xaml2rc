#include "listbox.hpp"
#include "fontmetrics.hpp"

listbox::listbox(YGNodeRef node) :
  widget(node) {
  YGNodeStyleSetMinHeight(node_, font_metrics::instance().dlu_to_dip_y(14));
}

std::string_view listbox::resource_class() const {
  return "LISTBOX";
}
