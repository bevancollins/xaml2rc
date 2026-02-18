#include "resource.hpp"
#include <format>
#include <ranges>

void resource::process_xaml(const pugi::xml_node& xaml) {
  nodecontext::process_xaml(xaml);

  auto name = xaml.attribute("x:Name");
  if (name)
    id_ = name.value();

  auto visibility = std::string_view{ xaml.attribute("Visibility").value() };
  if (visibility == "Hidden")
    style_.push_back("NOT WS_VISIBLE");
}

void resource::output(std::ostream& os) const {
  auto cls = resource_class();
  if (cls.empty())
    return;

  os << std::format("{} {}, {}, {}, {}, {}", cls, id_, x(), y(), width(), height());

  if (!style_.empty())
    os << std::format(", {}", style());

  if (!extended_style_.empty()) {
    if (style_.empty())
      os << ", ";
    os << std::format(", {}", extended_style());
  }

  os << "\n";

  nodecontext::output(os);
}

std::string resource::x() const {
  auto n = const_cast<YGNodeRef>(node_);
  float x{};
  while(n) {
    x += YGNodeLayoutGetLeft(n); // returns the relative left from parent
    n = YGNodeGetParent(n);
  }

  return std::to_string(std::lround(x));
}

std::string resource::y() const {
  auto n = const_cast<YGNodeRef>(node_);
  float y{};
  while(n) {
    y += YGNodeLayoutGetTop(n); // returns the relative top from parent
    n = YGNodeGetParent(n);
  }

  return std::to_string(std::lround(y));
}

std::string resource::width() const {
  return std::to_string(std::lround(YGNodeLayoutGetWidth(node_)));
}

std::string resource::height() const {
  return std::to_string(std::lround(YGNodeLayoutGetHeight(node_)));
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
