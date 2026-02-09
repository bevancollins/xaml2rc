#pragma once

#include "resource.hpp"

class edittext : public resource {
public:
  std::string_view resource_class() const override;
  void to_rc(YGNodeConstRef node, std::ostream& os) const override;
  YGSize measure(YGNodeConstRef node, float width, YGMeasureMode width_mode, float height, YGMeasureMode height_mode) override;

private:
  static const int default_height_dlu{14};
};
