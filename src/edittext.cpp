#include "edittext.hpp"

edittext::edittext(YGNodeRef node) :
  widget(node) {
  YGNodeStyleSetHeight(node_, 14.0f);
}

std::string_view edittext::resource_class() const {
  return "EDITTEXT";
}
