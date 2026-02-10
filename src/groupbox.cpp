#include "groupbox.hpp"
#include <format>

std::string_view groupbox::resource_class() const {
  return "GROUPBOX";
}

void groupbox::to_rc(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), header_, id_, x(node), y(node), width(node), height(node));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

YGNodeRef groupbox::from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = widget::from_xaml(xaml, parent);

  auto header = xaml.attribute("Header");
  if (header)
    header_ = header.as_string();

  return node;
}
