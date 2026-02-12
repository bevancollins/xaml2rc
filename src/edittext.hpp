#pragma once

#include "widget.hpp"

class edittext : public widget {
public:
  using widget::widget;

  std::string_view resource_class() const override;
};
