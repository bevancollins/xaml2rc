#include "control.hpp"
#include <format>

std::string control::position_string(YGNodeConstRef node) const {
  return std::format("{}, {}, {}, {}",
      YGNodeLayoutGetLeft(node),
      YGNodeLayoutGetTop(node),
      YGNodeLayoutGetWidth(node),
      YGNodeLayoutGetHeight(node));
}
