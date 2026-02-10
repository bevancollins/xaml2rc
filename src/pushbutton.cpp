#include "pushbutton.hpp"

std::string_view pushbutton::resource_class() const {
  return "PUSHBUTTON";
}

YGNodeRef pushbutton::from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = text_widget::from_xaml(xaml, parent);

  auto is_default = xaml.attribute("IsDefault");
  if (is_default.as_bool() && id_ == "-1")
    id_ = "IDOK";

  auto is_cancel = xaml.attribute("IsCancel");
  if (is_cancel.as_bool() && id_ == "-1")
    id_ = "IDCANCEL";

  return node;
}
