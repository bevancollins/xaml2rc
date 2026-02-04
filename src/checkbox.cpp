#include "checkbox.hpp"

std::string_view checkbox::resource_class() const {
  return "CHECKBOX";
}

void checkbox::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  common_text_control::from_xaml(xaml, node);
}
