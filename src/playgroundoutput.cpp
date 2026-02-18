#include "playgroundoutput.hpp"
#include <vector>
#include <format>

void playground_output::output(YGNodeRef root, std::ostream& out) {
  out << "<Layout config={{useWebDefaults: false}}>\n";
  print_node(root, out, 1);
  out << "</Layout>\n";
}

void playground_output::print_node(YGNodeRef node, std::ostream& out, int indent_level) {
  out << std::format("{:<{}}<Node style={{{{", "", indent_level * 2);

  // Flexbox properties
  if (YGNodeStyleGetFlexDirection(node) != YGFlexDirectionColumn)
    out << std::format("flexDirection: '{}', ", YGFlexDirectionToString(YGNodeStyleGetFlexDirection(node)));

  if (YGNodeStyleGetJustifyContent(node) != YGJustifyFlexStart)
    out << std::format("justifyContent: '{}', ", YGJustifyToString(YGNodeStyleGetJustifyContent(node)));

  if (YGNodeStyleGetAlignItems(node) != YGAlignStretch)
    out << std::format("alignItems: '{}', ", YGAlignToString(YGNodeStyleGetAlignItems(node)));

  if (YGNodeStyleGetAlignSelf(node) != YGAlignAuto)
    out << std::format("alignSelf: '{}', ", YGAlignToString(YGNodeStyleGetAlignSelf(node)));

  if (YGNodeStyleGetAlignContent(node) != YGAlignFlexStart)
    out << std::format("alignContent: '{}', ", YGAlignToString(YGNodeStyleGetAlignContent(node)));

  if (YGNodeStyleGetFlexWrap(node) != YGWrapNoWrap)
    out << std::format("flexWrap: '{}', ", YGWrapToString(YGNodeStyleGetFlexWrap(node)));

  // Flex properties
  if (YGNodeStyleGetFlexGrow(node) != 0.0f)
    out << std::format("flexGrow: {}, ", YGNodeStyleGetFlexGrow(node));

  if (YGNodeStyleGetFlexShrink(node) != 1.0f)
    out << std::format("flexShrink: {}, ", YGNodeStyleGetFlexShrink(node));

  YGValue flexBasis = YGNodeStyleGetFlexBasis(node);
  if (flexBasis.unit != YGUnitAuto)
    out << std::format("flexBasis: {}, ", value_to_string(flexBasis));

  // Sizing
  auto width = YGNodeStyleGetWidth(node);
  if (width.unit != YGUnitAuto)
    out << std::format("width: {}, ", value_to_string(width));

  auto height = YGNodeStyleGetHeight(node);
  if (height.unit != YGUnitAuto)
    out << std::format("height: {}, ", value_to_string(height));

  auto min_width = YGNodeStyleGetMinWidth(node);
  if (min_width.unit != YGUnitUndefined)
    out << std::format("minWidth: {}, ", value_to_string(min_width));

  auto min_height = YGNodeStyleGetMinHeight(node);
  if (min_height.unit != YGUnitUndefined)
    out << std::format("minHeight: {}, ", value_to_string(min_height));

  auto max_width = YGNodeStyleGetMaxWidth(node);
  if (max_width.unit != YGUnitUndefined)
    out << std::format("maxWidth: {}, ", value_to_string(max_width));

  auto max_height = YGNodeStyleGetMaxHeight(node);
  if (max_height.unit != YGUnitUndefined)
    out << std::format("maxHeight: {}, ", value_to_string(max_height));

  // Spacing (only individual edges for now)
  const YGEdge individual_edges[] = {YGEdgeLeft, YGEdgeTop, YGEdgeRight, YGEdgeBottom};
  const char* individual_edge_suffixes[] = {"Left", "Top", "Right", "Bottom"};

  for(int i = 0; i < 4; ++i) { // Loop only for specific edges
    auto margin = YGNodeStyleGetMargin(node, individual_edges[i]);
    if(margin.unit != YGUnitUndefined)
      out << std::format("margin{}: {}, ", individual_edge_suffixes[i], value_to_string(margin));

    auto padding = YGNodeStyleGetPadding(node, individual_edges[i]);
    if(padding.unit != YGUnitUndefined)
      out << std::format("padding{}: {}, ", individual_edge_suffixes[i], value_to_string(padding));

    auto border = YGNodeStyleGetBorder(node, individual_edges[i]);
    if(!std::isnan(border) && border > 0)
      out << std::format("border{}Width: {}, ", individual_edge_suffixes[i], border);
  }

  // Position
  const YGEdge pos_edges[] = {YGEdgeLeft, YGEdgeTop, YGEdgeRight, YGEdgeBottom};
  const char* pos_edge_names[] = {"left", "top", "right", "bottom"};
  if (YGNodeStyleGetPositionType(node) != YGPositionTypeStatic)
    out << std::format("position: '{}', ", YGPositionTypeToString(YGNodeStyleGetPositionType(node)));

  for(int i = 0; i < 4; ++i) {
    auto pos = YGNodeStyleGetPosition(node, pos_edges[i]);
    if(pos.unit != YGUnitUndefined)
      out << std::format("{}: {}, ", pos_edge_names[i], value_to_string(pos));
  }

  out << "}}";

  auto child_count = YGNodeGetChildCount(node);
  if (child_count > 0) {
    out << ">\n";
    for (uint32_t i = 0; i < child_count; ++i)
      print_node(YGNodeGetChild(node, i), out, indent_level + 1);

    out << std::format("{:<{}}</Node>\n", "", indent_level * 2);
  } else {
    out << " />\n";
  }
}

std::string playground_output::value_to_string(const YGValue& value) {
  switch(value.unit) {
    case YGUnitAuto:
      return "'auto'";
    case YGUnitPoint:
      return std::format("{}", value.value);
    case YGUnitPercent:
      return std::format("'{}%'", value.value);
    default:
      return "undefined";
  }
}
