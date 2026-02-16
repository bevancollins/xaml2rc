#include "groupbox.hpp"
#include <format>
#include "fontmetrics.hpp"

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
  YGNodeStyleSetGap(node_, YGGutterRow, font_metrics::instance().dlu_to_dip_x(4));
  YGNodeStyleSetGap(node_, YGGutterColumn, font_metrics::instance().dlu_to_dip_x(4));

  YGNodeStyleSetPadding(node_, YGEdgeTop, font_metrics::instance().dlu_to_dip_y(12));
  YGNodeStyleSetPadding(node_, YGEdgeLeft, font_metrics::instance().dlu_to_dip_y(9));
  YGNodeStyleSetPadding(node_, YGEdgeBottom, font_metrics::instance().dlu_to_dip_y(7));
  YGNodeStyleSetPadding(node_, YGEdgeRight, font_metrics::instance().dlu_to_dip_y(7));

  resource::process_xaml(xaml);

  auto header = xaml.attribute("Header");
  if (header)
    header_ = header.as_string();
}
