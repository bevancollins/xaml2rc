#pragma once

#include "common_text_control.hpp"

class checkbox : public common_text_control {
public:
  std::string_view resource_class() const override;
  void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
};
