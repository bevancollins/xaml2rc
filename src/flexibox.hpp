#pragma once

#include "resource.hpp"

class flexibox : public resource {
public:
  using resource::resource;

  std::string_view resource_class() const override;
  void output(YGNodeConstRef node, std::ostream& os) const override;
  YGNodeRef from_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent) override;

private:
  static YGJustify parse_justify(std::string_view alignment);
  static YGAlign parse_align(std::string_view alignment);
};
