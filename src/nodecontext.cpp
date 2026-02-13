#include "nodecontext.hpp"
#include <ranges>

nodecontext::nodecontext(YGNodeRef node) :
  node_(node) {
  YGNodeSetContext(node, this);
}

void nodecontext::process_xaml(const pugi::xml_node& xaml) {
  auto height = xaml.attribute("Height");
  if (height)
    YGNodeStyleSetHeight(node_, height.as_float());

  auto width = xaml.attribute("Width");
  if (width)
    YGNodeStyleSetWidth(node_, width.as_float());

  auto margin = xaml.attribute("Margin");
  if (margin) {
    auto margin_sv = std::string_view{margin.value()};
    if (margin_sv.find_first_of(',') != std::string_view::npos) {
      auto margin_array = parse_quad(margin.value());
      YGNodeStyleSetMargin(node_, YGEdgeLeft,   margin_array[0]);
      YGNodeStyleSetMargin(node_, YGEdgeRight,  margin_array[1]);
      YGNodeStyleSetMargin(node_, YGEdgeTop,    margin_array[2]);
      YGNodeStyleSetMargin(node_, YGEdgeBottom, margin_array[3]);
    } else {
      YGNodeStyleSetMargin(node_, YGEdgeAll, margin.as_float());
    }
  }

  auto padding = xaml.attribute("Padding");
  if (padding) {
    auto padding_sv = std::string_view{padding.value()};
    if (padding_sv.find_first_of(',') != std::string_view::npos) {
      auto padding_array = parse_quad(padding.value());
      YGNodeStyleSetPadding(node_, YGEdgeLeft,   padding_array[0]);
      YGNodeStyleSetPadding(node_, YGEdgeRight,  padding_array[1]);
      YGNodeStyleSetPadding(node_, YGEdgeTop,    padding_array[2]);
      YGNodeStyleSetPadding(node_, YGEdgeBottom, padding_array[3]);
    } else {
      YGNodeStyleSetPadding(node_, YGEdgeAll, padding.as_float());
    }
  }

  // HorizontalAlignment and VerticalAlignment control how this element aligns itself within its parent.
  // In Yoga, YGNodeStyleSetAlignSelf controls alignment along the *cross axis* relative to its parent.
  // If both HorizontalAlignment and VerticalAlignment are present, the last one parsed will take precedence for AlignSelf.
  auto horizontal_alignment = xaml.attribute("HorizontalAlignment");
  if (horizontal_alignment)
    YGNodeStyleSetAlignSelf(node_, parse_align(horizontal_alignment.value()));

  auto vertical_alignment = xaml.attribute("VerticalAlignment");
  if (vertical_alignment)
    YGNodeStyleSetAlignSelf(node_, parse_align(vertical_alignment.value()));
}

void nodecontext::output(std::ostream& os) const {
  output_children(node_, os);
}

void nodecontext::output_children(YGNodeRef node, std::ostream& os) {
  auto child_count = YGNodeGetChildCount(node);
  for (size_t i = 0; i < child_count; i++) {
    auto child = YGNodeGetChild(const_cast<YGNodeRef>(node), i);
    auto context = reinterpret_cast<nodecontext*>(YGNodeGetContext(child));
    if (context)
      context->output(os);
    else
      output_children(child, os);
  }
}

// parse 4 comma seperated values
std::array<int, 4> nodecontext::parse_quad(std::string_view input) {
  std::array<int, 4> result{};
  std::size_t index = 0;

  for (auto part : input | std::views::split(',')) {
    std::string_view token{part.begin(), part.end()};
    std::from_chars(token.data(), token.data() + token.size(), result[index++]);
  }

  return result;
}

YGJustify nodecontext::parse_justify(std::string_view alignment) const {
  if (alignment == "Left" || alignment == "Top")
    return YGJustifyFlexStart;
  else if (alignment == "Center")
    return YGJustifyCenter;
  else if (alignment == "Right" || alignment == "Bottom")
    return YGJustifyFlexEnd;
  else
    return YGJustifyFlexStart;
}

YGAlign nodecontext::parse_align(std::string_view alignment) const {
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
