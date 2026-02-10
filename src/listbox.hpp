#pragma once

#include "widget.hpp"

class listbox : public widget {
public:
  std::string_view resource_class() const override;
};
