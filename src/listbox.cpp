#include "listbox.hpp"

listbox::listbox(YGNodeRef node) :
  widget(node) {
  YGNodeStyleSetMinHeight(node_, 14.0f);
}

std::string_view listbox::resource_class() const {
  return "LISTBOX";
}
