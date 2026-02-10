#pragma once

#include "common_text_control.hpp"

class pushbutton : public common_text_control {
public:
  std::string_view resource_class() const override;
  YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
};
