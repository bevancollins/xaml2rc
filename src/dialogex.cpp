#include "dialogex.hpp"
#include <format>

std::string_view dialogex::resource_class() const {
  return "DIALOGEX";
}

void dialogex::output(YGNodeConstRef node, std::ostream& os) const {
  os << std::format("{} {} {}, {}, {}, {}\n", id_, resource_class(), x(node), y(node), width(node), height(node));
  os << std::format("CAPTION \"{}\"\n", caption_);

  if (!style_.empty())
    os << std::format("STYLE {}\n", style());

  if (!extended_style_.empty())
    os << std::format("EXSTYLE {}\n", extended_style());

  os << std::format("FONT {}, \"{}\", {}, {}, {}\n", font_size_, font_face_, font_weight_, font_italic_ ? 1 : 0, font_char_set_);
}

void dialogex::from_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  resource::from_xaml(xaml, node);

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
}

std::string dialogex::font_face() const {
  return font_face_;
}

int dialogex::font_size() const {
  return font_size_;
}

int dialogex::font_weight() const {
  return font_weight_;
}

bool dialogex::font_italic() const {
  return font_italic_;
}

int dialogex::font_char_set() const {
  return font_char_set_;
}
