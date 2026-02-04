#include "resource.hpp"
#include <ranges>
#include "fontmetrics.hpp"

void resource::from_xaml(const pugi::xml_node& xaml, [[maybe_unused]] YGNodeRef node) {
  auto name = xaml.attribute("x:Name");
  if (name)
    id_ = name.value();

  auto height = xaml.attribute("Height");
  if (height)
    YGNodeStyleSetHeight(node, height.as_float());

  auto width = xaml.attribute("Width");
  if (width)
    YGNodeStyleSetWidth(node, width.as_float());

  auto margin = xaml.attribute("Margin");
  if (margin) {
    auto margin_array = parse_quad(margin.value());
    YGNodeStyleSetMargin(node, YGEdgeLeft,   margin_array[0]);
    YGNodeStyleSetMargin(node, YGEdgeRight,  margin_array[1]);
    YGNodeStyleSetMargin(node, YGEdgeTop,    margin_array[2]);
    YGNodeStyleSetMargin(node, YGEdgeBottom, margin_array[3]);
  }

  auto enabled = xaml.attribute("IsEnabled").as_bool(true);
  if (!enabled)
    style_.push_back("WS_DISABLED");

  auto visibility = std::string_view{ xaml.attribute("Visibility").value() };
  if (visibility == "Hidden")
    style_.push_back("NOT WS_VISIBLE");
}

std::string resource::x(YGNodeConstRef node) const {
  return std::to_string(font_metrics::instance().dip_to_dlu_x(YGNodeLayoutGetLeft(node)));
}

std::string resource::y(YGNodeConstRef node) const {
  return std::to_string(font_metrics::instance().dip_to_dlu_y(YGNodeLayoutGetTop(node)));
}

std::string resource::width(YGNodeConstRef node) const {
  return std::to_string(font_metrics::instance().dip_to_dlu_x(YGNodeLayoutGetWidth(node)));
}

std::string resource::height(YGNodeConstRef node) const {
  return std::to_string(font_metrics::instance().dip_to_dlu_y(YGNodeLayoutGetHeight(node)));
}

std::string resource::join_strings(const std::vector<std::string>& strings) const {
  auto view = strings | std::views::join_with(std::string{" | "});
  return std::string(view.begin(), view.end());
}

std::string resource::style() const {
  return join_strings(style_);
}

std::string resource::extended_style() const {
  return join_strings(extended_style_);
}

// parse 4 comma seperated values
std::array<int, 4> resource::parse_quad(std::string_view input) {
  std::array<int, 4> result{};
  std::size_t index = 0;

  for (auto part : input | std::views::split(',')) {
    std::string_view token{part.begin(), part.end()};
    std::from_chars(token.data(), token.data() + token.size(), result[index++]);
  }

  return result;
}
