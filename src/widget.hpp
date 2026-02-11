#pragma once

#include "resource.hpp"

class widget : public resource {
public:
  void process_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
  void measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) override;

  virtual int default_height_dlu() const;
};
