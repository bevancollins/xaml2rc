#pragma once

#include "resource.hpp"

class common_text_control : public resource {
public:
  virtual void to_rc(YGNodeConstRef node, std::ostream& os) const override;
  virtual YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
  virtual void measure(YGNodeConstRef node, float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode) override;

  virtual int default_height_dlu() const;

protected:
  std::string text_;
};
