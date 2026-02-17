#pragma once

#include "widget.hpp"

class listbox : public widget {
public:
  listbox(YGNodeRef node);

  std::string_view resource_class() const override;
};
