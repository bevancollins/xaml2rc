#pragma once

#include "widget.hpp"

class text_widget : public widget {
public:
  virtual void to_rc(YGNodeConstRef node, std::ostream& os) const override;
  virtual YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
  virtual void measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) override;

protected:
  std::string text_;
};
