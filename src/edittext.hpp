#pragma once

#include "resource.hpp"

class edittext : public resource {
public:
  std::string_view resource_class() const override;
  void output(YGNodeConstRef node, std::ostream& os) const override;
};
