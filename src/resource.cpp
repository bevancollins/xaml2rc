#include "resource.hpp"
#include <format>
#include <ranges>
#include "fontmetrics.hpp"

resource::resource(YGNodeRef node) :
  node_(node) {
  YGNodeSetContext(node, this);
}

void resource::process_xaml(const pugi::xml_node& xaml) {
  auto name = xaml.attribute("x:Name");
  if (name)
    id_ = name.value();

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

  auto visibility = std::string_view{ xaml.attribute("Visibility").value() };
  if (visibility == "Hidden")
    style_.push_back("NOT WS_VISIBLE");

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

  output_children(os);
}

void resource::output_children(std::ostream& os) const {
  auto child_count = YGNodeGetChildCount(node_);
  for (size_t i = 0; i < child_count; i++) {
    auto child = YGNodeGetChild(const_cast<YGNodeRef>(node_), i);
    auto context = reinterpret_cast<resource*>(YGNodeGetContext(child));
    if (context)
      context->output(os);
  }
}

void resource::measure([[maybe_unused]] float& width, [[maybe_unused]] YGMeasureMode& width_mode, [[maybe_unused]] float& height, [[maybe_unused]] YGMeasureMode& height_mode) {
}

std::string resource::x() const {
  auto n = const_cast<YGNodeRef>(node_);
  float x{};
  while(n) {
    x += YGNodeLayoutGetLeft(n); // returns the relative left from parent
    n = YGNodeGetParent(n);
  }

  return std::to_string(font_metrics::instance().dip_to_dlu_x(x));
}

std::string resource::y() const {
  auto n = const_cast<YGNodeRef>(node_);
  float y{};
  while(n) {
    y += YGNodeLayoutGetTop(n); // returns the relative top from parent
    n = YGNodeGetParent(n);
  }

  return std::to_string(font_metrics::instance().dip_to_dlu_y(y));
}

std::string resource::width() const {
  return std::to_string(font_metrics::instance().dip_to_dlu_x(YGNodeLayoutGetWidth(node_)));
}

std::string resource::height() const {
  return std::to_string(font_metrics::instance().dip_to_dlu_y(YGNodeLayoutGetHeight(node_)));
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

YGJustify resource::parse_justify(std::string_view alignment) const {
  if (alignment == "Left" || alignment == "Top")
    return YGJustifyFlexStart;
  else if (alignment == "Center")
    return YGJustifyCenter;
  else if (alignment == "Right" || alignment == "Bottom")
    return YGJustifyFlexEnd;
  else
    return YGJustifyFlexStart;
}

YGAlign resource::parse_align(std::string_view alignment) const {
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

void resource::finalise_layout() {
}
