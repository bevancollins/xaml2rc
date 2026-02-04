#include "flexibox.hpp"

std::string_view flexibox::resource_class() const {
  return "";
}

void flexibox::output([[maybe_unused]] YGNodeConstRef node, [[maybe_unused]] std::ostream& os) const {
}

void flexibox::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::from_xaml(xaml, node);

/*  std::string_view orientation { xaml.attribute("Orientation").as_string("Vertical") };
  if (orientation == "Horizontal")
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
  else if (orientation == "Vertical")
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
  else
    throw std::runtime_error(std::format("unrecognised Orientation ({})", orientation));*/
}
