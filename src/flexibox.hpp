#pragma once

#include "control.hpp"

class flexibox : public control {
public:
  void output(YGNodeConstRef node, std::ostream& os) const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
};
