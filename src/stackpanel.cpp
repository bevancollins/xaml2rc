#include "stackpanel.hpp"
#include "fontmetrics.hpp"

void stackpanel::process_xaml(const pugi::xml_node& xaml) {
  YGNodeStyleSetGap(node_, YGGutterRow, font_metrics::instance().dlu_to_dip_x(4));
  YGNodeStyleSetGap(node_, YGGutterColumn, font_metrics::instance().dlu_to_dip_x(4));

  nodecontext::process_xaml(xaml);

  std::string_view orientation          { xaml.attribute("Orientation").as_string("Vertical") };
  std::string_view vertical_alignment   { xaml.attribute("VerticalAlignment").as_string("Stretch") };
  std::string_view horizontal_alignment { xaml.attribute("HorizontalAlignment").as_string("Stretch") };

  if (orientation == "Horizontal") {
    YGNodeStyleSetFlexDirection(node_, YGFlexDirectionRow);
    YGNodeStyleSetJustifyContent(node_, parse_justify(horizontal_alignment));
    YGNodeStyleSetAlignItems(node_, parse_align(vertical_alignment));
  } else if (orientation == "Vertical") {
    YGNodeStyleSetFlexDirection(node_, YGFlexDirectionColumn);
    YGNodeStyleSetJustifyContent(node_, parse_justify(vertical_alignment));
    YGNodeStyleSetAlignItems(node_, parse_align(horizontal_alignment));
  } else {
    throw std::runtime_error(std::format("unrecognised Orientation ({})", orientation));
  }
}
