#include "radiobutton.hpp"

radiobutton::radiobutton(YGNodeRef node) :
  text_widget(node) {
  YGNodeStyleSetHeight(node_, 10.0f);
}

std::string_view radiobutton::resource_class() const {
  return "RADIOBUTTON";
}
