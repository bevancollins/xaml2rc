#pragma once

#include "widget.hpp"

class text_widget : public widget {
public:
  virtual void output(YGNodeConstRef node, std::ostream& os) const override;
  virtual void process_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
  virtual void measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) override;

protected:
  std::string text_;
};
