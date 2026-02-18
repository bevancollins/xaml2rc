#include "combobox.hpp"
#include <string_view>

combobox::combobox(YGNodeRef node) :
  widget(node) {
  YGNodeStyleSetHeight(node_, 12.0f);
}

std::string_view combobox::resource_class() const {
  return "COMBOBOX";
}

void combobox::process_xaml(const pugi::xml_node& xaml) {
  widget::process_xaml(xaml);

  auto scrollbar_visibility = std::string_view{xaml.attribute("ScrollViewer.VerticalScrollBarVisibility").as_string("Visible")};
  if (scrollbar_visibility != "Disabled" && scrollbar_visibility != "Hidden")
    style_.push_back("WS_VSCROLL");
}
