#include "pushbutton.hpp"

std::string_view pushbutton::resource_class() const {
  return "PUSHBUTTON";
}

void pushbutton::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  text_widget::process_xaml(xaml, node);

  auto is_default = xaml.attribute("IsDefault");
  if (is_default.as_bool() && id_ == "-1")
    id_ = "IDOK";

  auto is_cancel = xaml.attribute("IsCancel");
  if (is_cancel.as_bool() && id_ == "-1")
    id_ = "IDCANCEL";
}
