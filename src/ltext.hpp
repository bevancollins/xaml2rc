#pragma once

#include "common_text_control.hpp"

class ltext : public common_text_control {
public:
  std::string_view resource_class() const override;
  YGSize measure(float width, YGMeasureMode width_mode, float height, YGMeasureMode height_mode) override;

private:
  static const int default_height_per_line_dlu{8};
};
