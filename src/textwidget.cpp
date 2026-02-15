#include "textwidget.hpp"
#include <algorithm>
#include <format>
#include "fontmetrics.hpp"

void text_widget::output(std::ostream& os) const {
  os << std::format("{} \"{}\", {}, {}, {}, {}, {}", resource_class(), text_, id_, x(), y(), width(), height());

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";
}

void text_widget::process_xaml(const pugi::xml_node& xaml) {
  widget::process_xaml(xaml);

  auto content = xaml.attribute("Content");
  if (content)
    text_ = content.value();

  // Calculate intrinsic width based on text
  YGNodeStyleSetMinWidth(node_, font_metrics::instance().measure_text_width_dip(text_));
}
