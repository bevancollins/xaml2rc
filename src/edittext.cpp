#include "edittext.hpp"
#include <format>

std::string_view edittext::resource_class() const {
  return "EDITTEXT";
}

void edittext::output(YGNodeConstRef node, const resource::font_metrics& fm, std::ostream& os) const {
  os << std::format("{} {}, {}, {}, {}, {}", resource_class(), id_, x(node, fm), y(node, fm), width(node, fm), height(node, fm));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}
