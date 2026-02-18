#include "groupbox.hpp"
#include <format>

std::string_view groupbox::resource_class() const {
  return "GROUPBOX";
}

void groupbox::output(std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), header_, id_, x(), y(), width(), height());

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";

  nodecontext::output(os);
}

void groupbox::process_xaml(const pugi::xml_node& xaml) {
  YGNodeStyleSetGap(node_, YGGutterRow,    4.0f);
  YGNodeStyleSetGap(node_, YGGutterColumn, 4.0f);

  YGNodeStyleSetPadding(node_, YGEdgeTop,   12.0f);
  YGNodeStyleSetPadding(node_, YGEdgeLeft,   9.0f);
  YGNodeStyleSetPadding(node_, YGEdgeBottom, 7.0f);
  YGNodeStyleSetPadding(node_, YGEdgeRight,  7.0f);

  resource::process_xaml(xaml);

  auto header = xaml.attribute("Header");
  if (header)
    header_ = header.as_string();
}
