#pragma once

#include <string>
#include "control.hpp"

class dialogex : public control {
public:
  void output(YGNodeConstRef node, std::ostream& os) const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;

  std::string caption;
};
