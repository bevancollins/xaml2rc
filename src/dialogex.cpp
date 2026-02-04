#include "dialogex.hpp"
#include <format>

void dialogex::output(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} DIALOGEX {}\n", id, position_string(node));
  os << std::format("CAPTION {}\n", caption);
}

void dialogex::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  auto height = xaml.attribute("Height");
  if (height)
    YGNodeStyleSetHeight(node, height.as_float());

  auto width = xaml.attribute("Width");
  if (width)
    YGNodeStyleSetWidth(node, width.as_float());

  auto title = xaml.attribute("Title");
  if (title)
    caption = title.value();
}
