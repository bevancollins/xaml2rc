#pragma once

#include "common_text_control.hpp"

class ltext : public common_text_control {
public:
  std::string_view resource_class() const override;

  int default_height_dlu() const override;
};
