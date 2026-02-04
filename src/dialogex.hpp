#pragma once

#include <windows.h>
#include <string>
#include "resource.hpp"

class dialogex : public resource {
public:
  std::string_view resource_class() const override;
  void output(YGNodeConstRef node, const resource::font_metrics& fm, std::ostream& os) const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;

  std::string font_face() const;
  int font_size() const;
  int font_weight() const;
  bool font_italic() const;
  int font_char_set() const;

private:
  std::string caption_;
  std::string font_face_{"Segoe UI"};
  int font_size_{12};
  int font_weight_{FW_NORMAL};
  bool font_italic_{false};
  int font_char_set_{DEFAULT_CHARSET};
};
