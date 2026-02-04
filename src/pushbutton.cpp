#include "pushbutton.hpp"
#include <format>

void pushbutton::output(YGNodeConstRef node, std::ostream& out) const {
  out << std::format("PUSHBUTTON {}, {}, {}\n", text, id, position_string(node));
}

void pushbutton::from_xaml(const pugi::xml_node& xaml, [[maybe_unused]] YGNodeRef node) {
  auto content = xaml.attribute("Content");
  if (content)
    text = content.value();

  auto is_default = xaml.attribute("IsDefault");
  if (is_default.as_bool())
    id = "IDOK";

  auto is_cancel = xaml.attribute("IsCancel");
  if (is_cancel.as_bool())
    id = "IDCANCEL";
}
