#include "groupbox.hpp"
#include <format>
#include "fontmetrics.hpp"

std::string_view groupbox::resource_class() const {
  return "GROUPBOX";
}

void groupbox::output(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), header_, id_, x(node), y(node), width(node), height(node));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";

  output_children(node, os);
}

YGNodeRef groupbox::process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = widget::process_xaml(xaml, parent);

  auto header = xaml.attribute("Header");
  if (header)
    header_ = header.as_string();

  // add padding to the top
  if (YGNodeStyleGetPadding(node, YGEdgeTop).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeTop, font_metrics::instance().dlu_to_dip_y(12));

  // and to the left
  if (YGNodeStyleGetPadding(node, YGEdgeLeft).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeLeft, font_metrics::instance().dlu_to_dip_y(9));

  // and to the bottom
  if (YGNodeStyleGetPadding(node, YGEdgeBottom).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeBottom, font_metrics::instance().dlu_to_dip_y(7));

  // and to the right
  if (YGNodeStyleGetPadding(node, YGEdgeRight).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeRight, font_metrics::instance().dlu_to_dip_y(7));

  return node;
}
