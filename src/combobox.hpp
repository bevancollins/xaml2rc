#pragma once

#include "widget.hpp"

class combobox : public widget {
public:
  using widget::widget;

  std::string_view resource_class() const override;
  void process_xaml(const pugi::xml_node& xaml) override;
  int default_height_dlu() const override;
};
