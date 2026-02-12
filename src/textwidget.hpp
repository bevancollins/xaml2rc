#pragma once

#include "widget.hpp"

class text_widget : public widget {
public:
  using widget::widget;

  virtual void output(std::ostream& os) const override;
  virtual void process_xaml(const pugi::xml_node& xaml) override;
  virtual void measure(float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) override;

protected:
  std::string text_;
};
