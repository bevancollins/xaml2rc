#pragma once

#include "resource.hpp"

class listbox : public resource {
public:
  std::string_view resource_class() const override;
};
