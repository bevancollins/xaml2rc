#pragma once

#include "widget.hpp"

class edittext : public widget {
public:
  std::string_view resource_class() const override;
};
