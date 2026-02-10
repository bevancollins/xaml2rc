#include "combobox.hpp"
#include <string_view>

std::string_view combobox::resource_class() const {
  return "COMBOBOX";
}

YGNodeRef combobox::process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = widget::process_xaml(xaml, parent);

  auto scrollbar_visibility = std::string_view{xaml.attribute("ScrollViewer.VerticalScrollBarVisibility").as_string("Visible")};
  if (scrollbar_visibility != "Disabled" && scrollbar_visibility != "Hidden")
    style_.push_back("WS_VSCROLL");

  return node;
}

int combobox::default_height_dlu() const {
  return 12;
}
