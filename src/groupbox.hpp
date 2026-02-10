#pragma once

#include "widget.hpp"
#include <string>

class groupbox : public widget {
public:
  std::string_view resource_class() const override;
  virtual void to_rc(YGNodeConstRef node, std::ostream& os) const override;
  YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;

private:
  std::string header_;
};
