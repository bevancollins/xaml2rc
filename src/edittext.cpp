#include "edittext.hpp"
#include <format>
#include "fontmetrics.hpp"

std::string_view edittext::resource_class() const {
  return "EDITTEXT";
}

void edittext::to_rc(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} {}, {}, {}, {}, {}", resource_class(), id_, x(node), y(node), width(node), height(node));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}
