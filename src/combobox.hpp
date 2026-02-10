#pragma once

#include "resource.hpp"

class combobox : public resource {
public:
  std::string_view resource_class() const override;
  YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
};
