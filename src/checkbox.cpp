#include "checkbox.hpp"

checkbox::checkbox(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, 10.0f);
}

std::string_view checkbox::resource_class() const {
  return "CHECKBOX";
}
