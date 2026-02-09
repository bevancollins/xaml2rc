#pragma once

#include "resource.hpp"

class common_text_control : public resource {
public:
  void to_rc(YGNodeConstRef node, std::ostream& os) const override;
  YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;

protected:
  std::string text_;
};
