#pragma once

#include "common_text_control.hpp"

class pushbutton : public common_text_control {
public:
  std::string_view resource_class() const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
  YGSize measure(float width, YGMeasureMode width_mode, float height, YGMeasureMode height_mode) override;

private:
  static const int default_height_dlu{14};
  static const int default_width_dlu{50};
};
