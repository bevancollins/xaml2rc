#pragma once

#include "resource.hpp"

class stackpanel : public resource {
public:
  using resource::resource;

  std::string_view resource_class() const override;
  void output(YGNodeConstRef node, std::ostream& os) const override;
  YGNodeRef process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;
};
