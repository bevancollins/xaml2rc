#pragma once

#include "textwidget.hpp"

class checkbox : public text_widget {
public:
  using text_widget::text_widget;

  std::string_view resource_class() const override;

  int default_height_dlu() const override;
};
