#include "flexibox.hpp"

std::string_view flexibox::resource_class() const {
  return {};
}

void flexibox::to_rc([[maybe_unused]] YGNodeConstRef node, [[maybe_unused]] std::ostream& os) const {
}

YGNodeRef flexibox::from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) {
  auto node = resource::from_xaml(xaml, parent);

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

  return node;
}
