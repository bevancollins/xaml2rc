#include "dialogex.hpp"
#include <format>
#include "fontmetrics.hpp"

std::string_view dialogex::resource_class() const {
  return "DIALOGEX";
}

void dialogex::output(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} {} 0, 0, {}, {}\n", id_, resource_class(), width(node), height(node));
  os << std::format("CAPTION \"{}\"\n", caption_);

  if (!style_.empty())
    os << std::format("STYLE {}\n", style());

  if (!extended_style_.empty())
    os << std::format("EXSTYLE {}\n", extended_style());

  os << std::format("FONT {}, \"{}\", {}, {}, {:#x}\n", font_size_, font_face_, font_weight_, font_italic_ ? 1 : 0, font_char_set_);

  os << "BEGIN\n";
  output_children(node, os);
  os << "END\n";
}

void dialogex::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  auto title = xaml.attribute("Title");
  if (title)
    caption_ = title.value();

  auto font_family = xaml.attribute("FontFamily");
  if (font_family)
    font_face_ = font_family.value();

  auto font_size = xaml.attribute("FontSize");
  if (font_size)
    font_size_ = font_size.as_int();

  auto font_style = std::string_view {xaml.attribute("FontStyle").as_string("")};
  font_italic_ = font_style == "Italic";

  auto font_weight = std::string_view {xaml.attribute("FontWeight").as_string("Normal")};
  if (font_weight == "Thin")
    font_weight_ = FW_THIN;
  else if (font_weight == "ExtraLight")
    font_weight_ = FW_EXTRALIGHT;
  else if (font_weight == "Light")
    font_weight_ = FW_LIGHT;
  else if (font_weight == "Normal")
    font_weight_ = FW_NORMAL;
  else if (font_weight == "Medium")
    font_weight_ = FW_MEDIUM;
  else if (font_weight == "SemiBold")
    font_weight_ = FW_SEMIBOLD;
  else if (font_weight == "Bold")
    font_weight_ = FW_BOLD;
  else if (font_weight == "ExtraBold")
    font_weight_ = FW_EXTRABOLD;
  else if (font_weight == "Heavy")
    font_weight_ = FW_HEAVY;
  else
    throw std::runtime_error(std::format("unrecognised FontWeight ({})", font_weight));

  auto top_most = xaml.attribute("Topmost").as_bool(false);
  if (top_most)
    extended_style_.push_back("WS_EX_TOPMOST");

  font_metrics::instance().initialise(font_face_.c_str(), font_size_, font_weight_, font_italic_, font_char_set_);

  resource::process_xaml(xaml, node);
}

void dialogex::finalise_layout(YGNodeRef node) {
  // add padding to the top
  if (YGNodeStyleGetPadding(node, YGEdgeTop).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeTop, font_metrics::instance().dlu_to_dip_y(7));

  // and to the left
  if (YGNodeStyleGetPadding(node, YGEdgeLeft).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeLeft, font_metrics::instance().dlu_to_dip_y(7));

  // and to the bottom
  if (YGNodeStyleGetPadding(node, YGEdgeBottom).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeBottom, font_metrics::instance().dlu_to_dip_y(7));

  // and to the right
  if (YGNodeStyleGetPadding(node, YGEdgeRight).unit == YGUnitUndefined)
    YGNodeStyleSetPadding(node, YGEdgeRight, font_metrics::instance().dlu_to_dip_y(7));
}
