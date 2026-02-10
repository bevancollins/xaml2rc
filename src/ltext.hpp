#pragma once

#include "textwidget.hpp"

class ltext : public text_widget {
public:
  std::string_view resource_class() const override;

  int default_height_dlu() const override;
};
