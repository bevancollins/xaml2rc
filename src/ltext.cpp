#include "ltext.hpp"

ltext::ltext(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, 8.0f);
}

std::string_view ltext::resource_class() const {
  return "LTEXT";
}
