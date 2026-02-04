#include "flexibox.hpp"

std::string_view flexibox::resource_class() const {
  return {};
}

void flexibox::output([[maybe_unused]] YGNodeConstRef node, [[maybe_unused]] std::ostream& os) const {
}

void flexibox::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::from_xaml(xaml, node);

  std::string_view orientation          { xaml.attribute("Orientation").as_string("Vertical") };
  std::string_view vertical_alignment   { xaml.attribute("VerticalAlignment").as_string("Stretch") };
  std::string_view horizontal_alignment { xaml.attribute("HorizontalAlignment").as_string("Stretch") };

  if (orientation == "Horizontal") {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
    YGNodeStyleSetJustifyContent(node, flexibox::parse_justify(horizontal_alignment));
    YGNodeStyleSetAlignItems(node, flexibox::parse_align(vertical_alignment));
  } else if (orientation == "Vertical") {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
    YGNodeStyleSetJustifyContent(node, flexibox::parse_justify(vertical_alignment));
    YGNodeStyleSetAlignItems(node, flexibox::parse_align(horizontal_alignment));
  } else {
    throw std::runtime_error(std::format("unrecognised Orientation ({})", orientation));
  }
}

YGJustify flexibox::parse_justify(std::string_view alignment) {
  if (alignment == "Left" || alignment == "Top")
    return YGJustifyFlexStart;
  else if (alignment == "Center")
    return YGJustifyCenter;
  else if (alignment == "Right" || alignment == "Bottom")
    return YGJustifyFlexEnd;
  else
    return YGJustifyFlexStart;
}

YGAlign flexibox::parse_align(std::string_view alignment) {
  if (alignment == "Left" || alignment == "Top")
    return YGAlignFlexStart;
  else if (alignment == "Center")
    return YGAlignCenter;
  else if (alignment == "Right" || alignment == "Bottom")
    return YGAlignFlexEnd;
  else if (alignment == "Stretch")
    return YGAlignStretch;
  else
    return YGAlignStretch;
}
