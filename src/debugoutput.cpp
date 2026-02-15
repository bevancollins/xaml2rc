#include "debugoutput.hpp"

#include <cmath>
#include <format>
#include <ostream>
#include <print>
#include <string_view>

#include "nodecontext.hpp"
#include "resource.hpp"

void debug_output::output(YGNodeRef root, std::ostream& out) {
  print_node(root, out, 0);
}

std::string debug_output::value_to_string(const YGValue& value) {
  if (value.unit == YGUnitUndefined)
    return "undefined";
  if (value.unit == YGUnitAuto)
    return "auto";
  else
    return std::format("{} {}", value.value, YGUnitToString(value.unit));
}

void debug_output::print_node(YGNodeRef node, std::ostream& out, int level) {
  if (!node)
    return;

  auto indent = level * 2;
  auto context = reinterpret_cast<nodecontext*>(YGNodeGetContext(node));

  std::string_view resource_class("layout");
  if (context) {
    auto r = dynamic_cast<resource*>(context);
    if (r)
      resource_class = r->resource_class();
  }

  std::println(out, "{:<{}} {} [{}, {}, {}, {}]", "", indent, resource_class,
               YGNodeLayoutGetLeft(node), YGNodeLayoutGetTop(node),
               YGNodeLayoutGetWidth(node), YGNodeLayoutGetHeight(node));
  indent += 2;

  std::println(
      out,
      "{:<{}}flex-direction: {}, justify-content: {}, align-items: {}, "
      "align-self: {}, align-content: {}",
      "", indent, YGFlexDirectionToString(YGNodeStyleGetFlexDirection(node)),
      YGJustifyToString(YGNodeStyleGetJustifyContent(node)),
      YGAlignToString(YGNodeStyleGetAlignItems(node)),
      YGAlignToString(YGNodeStyleGetAlignSelf(node)),
      YGAlignToString(YGNodeStyleGetAlignContent(node)));

  std::println(out, "{:<{}}flex-wrap: {}, overflow: {}, display: {}", "", indent,
               YGWrapToString(YGNodeStyleGetFlexWrap(node)),
               YGOverflowToString(YGNodeStyleGetOverflow(node)),
               YGDisplayToString(YGNodeStyleGetDisplay(node)));

  std::println(out, "{:<{}}flex-grow: {}, flex-shrink: {}, flex-basis: {}", "",
               indent, YGNodeStyleGetFlexGrow(node), YGNodeStyleGetFlexShrink(node),
               value_to_string(YGNodeStyleGetFlexBasis(node)));

  auto width = YGNodeStyleGetWidth(node);
  auto height = YGNodeStyleGetHeight(node);
  if (width.unit != YGUnitUndefined || height.unit != YGUnitUndefined) {
    std::print(out, "{:<{}}", "", indent);
    if (width.unit != YGUnitUndefined)
      std::print(out, "width: {}  ", value_to_string(width));
    if (height.unit != YGUnitUndefined)
      std::print(out, "height: {}", value_to_string(height));
    std::println(out);
  }

  auto min_width = YGNodeStyleGetMinWidth(node);
  auto min_height = YGNodeStyleGetMinHeight(node);
  if (min_width.unit != YGUnitUndefined || min_height.unit != YGUnitUndefined) {
    std::print(out, "{:<{}}", "", indent);
    if (min_width.unit != YGUnitUndefined)
      std::print(out, "min-width: {}  ", value_to_string(min_width));
    if (min_height.unit != YGUnitUndefined)
      std::print(out, "min-height: {}", value_to_string(min_height));
    std::println(out);
  }

  auto max_width = YGNodeStyleGetMaxWidth(node);
  auto max_height = YGNodeStyleGetMaxHeight(node);
  if (max_width.unit != YGUnitUndefined || max_height.unit != YGUnitUndefined) {
    std::print(out, "{:<{}}", "", indent);
    if (max_width.unit != YGUnitUndefined)
      std::print(out, "max-width: {}  ", value_to_string(max_width));
    if (max_height.unit != YGUnitUndefined)
      std::print(out, "max-height: {}", value_to_string(max_height));
    std::println(out);
  }

  std::string margin_string;
  for (int i = YGEdgeLeft; i <= YGEdgeAll; ++i) {
    auto edge = static_cast<YGEdge>(i);
    YGValue margin = YGNodeStyleGetMargin(node, edge);
    if (margin.unit != YGUnitUndefined)
      margin_string +=
          std::format("{}: {}, ", YGEdgeToString(edge), value_to_string(margin));
  }
  if (!margin_string.empty())
    std::println(out, "{:<{}}margin: {}", "", indent, margin_string);

  std::string padding_string;
  for (int i = YGEdgeLeft; i <= YGEdgeAll; ++i) {
    auto edge = static_cast<YGEdge>(i);
    auto padding = YGNodeStyleGetPadding(node, edge);
    if (padding.unit != YGUnitUndefined)
      padding_string +=
          std::format("{}: {}, ", YGEdgeToString(edge), value_to_string(padding));
  }
  if (!padding_string.empty())
    std::println(out, "{:<{}}padding: {}", "", indent, padding_string);

  std::string border_string;
  for (int i = YGEdgeLeft; i <= YGEdgeAll; ++i) {
    auto edge = static_cast<YGEdge>(i);
    auto border = YGNodeStyleGetBorder(node, edge);
    if (!std::isnan(border))
      border_string += std::format("{}: {}, ", YGEdgeToString(edge), border);
  }
  if (!border_string.empty())
    std::println(out, "{:<{}}border: {}", "", indent, border_string);

  std::print(out, "{:<{}}position-type: {}", "", indent,
             YGPositionTypeToString(YGNodeStyleGetPositionType(node)));
  std::string position_string;
  for (int i = YGEdgeLeft; i <= YGEdgeBottom; ++i) {
    auto edge = static_cast<YGEdge>(i);
    auto position = YGNodeStyleGetPosition(node, edge);
    if (position.unit != YGUnitUndefined)
      position_string +=
          std::format("{}: {}, ", YGEdgeToString(edge), value_to_string(position));
  }
  if (!position_string.empty())
    std::print(out, "  position: {}", position_string);
  std::println(out, "");

  for (size_t i = 0; i < YGNodeGetChildCount(node); ++i)
    print_node(YGNodeGetChild(node, i), out, level + 1);
}
