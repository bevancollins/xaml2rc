#pragma once

#include "widget.hpp"

class listbox : public widget {
public:
  using widget::widget;

  std::string_view resource_class() const override;
};
