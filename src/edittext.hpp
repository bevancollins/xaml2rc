#pragma once

#include "widget.hpp"

class edittext : public widget {
public:
  edittext(YGNodeRef node);

  std::string_view resource_class() const override;
};
