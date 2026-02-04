#include "common_text_control.hpp"
#include <format>

void common_text_control::output(YGNodeConstRef node, const resource::font_metrics& fm, std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), text_, id_, x(node, fm), y(node, fm), width(node, fm), height(node, fm));

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

void common_text_control::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::from_xaml(xaml, node);

  auto content = xaml.attribute("Content");
  if (content)
    text_ = content.value();

  auto is_tab_stop = xaml.attribute("IsTabStop").as_bool(true);
  if (is_tab_stop)
    style_.push_back("WS_TABSTOP");
}
