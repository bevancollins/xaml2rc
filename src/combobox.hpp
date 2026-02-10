#pragma once

#include "widget.hpp"

class combobox : public widget {
public:
  std::string_view resource_class() const override;
  YGNodeRef process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
  int default_height_dlu() const override;
};
