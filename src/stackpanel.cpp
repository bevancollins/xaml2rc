#include "stackpanel.hpp"

std::string_view stackpanel::resource_class() const {
  return {};
}

void stackpanel::output(YGNodeConstRef node, std::ostream& os) const {
  output_children(node, os);
}

void stackpanel::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::process_xaml(xaml, node);

  std::string_view orientation          { xaml.attribute("Orientation").as_string("Vertical") };
  std::string_view vertical_alignment   { xaml.attribute("VerticalAlignment").as_string("Stretch") };
  std::string_view horizontal_alignment { xaml.attribute("HorizontalAlignment").as_string("Stretch") };

  if (orientation == "Horizontal") {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
    YGNodeStyleSetJustifyContent(node, parse_justify(horizontal_alignment));
    YGNodeStyleSetAlignItems(node, parse_align(vertical_alignment));
  } else if (orientation == "Vertical") {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
    YGNodeStyleSetJustifyContent(node, parse_justify(vertical_alignment));
    YGNodeStyleSetAlignItems(node, parse_align(horizontal_alignment));
  } else {
    throw std::runtime_error(std::format("unrecognised Orientation ({})", orientation));
  }
}
