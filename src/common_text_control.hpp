#pragma once

#include "resource.hpp"

class common_text_control : public resource {
public:
  void output(YGNodeConstRef node, std::ostream& os) const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;

protected:
  std::string text_;
};
