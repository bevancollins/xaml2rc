#pragma once

#include "widget.hpp"

class combobox : public widget {
public:
  combobox(YGNodeRef node);

  std::string_view resource_class() const override;
  void process_xaml(const pugi::xml_node& xaml) override;
};
