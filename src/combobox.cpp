#include "combobox.hpp"
#include <string_view>

std::string_view combobox::resource_class() const {
  return "COMBOBOX";
}

void combobox::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  widget::process_xaml(xaml, node);

  auto scrollbar_visibility = std::string_view{xaml.attribute("ScrollViewer.VerticalScrollBarVisibility").as_string("Visible")};
  if (scrollbar_visibility != "Disabled" && scrollbar_visibility != "Hidden")
    style_.push_back("WS_VSCROLL");
}

int combobox::default_height_dlu() const {
  return 12;
}
