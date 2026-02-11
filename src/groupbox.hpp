#pragma once

#include "widget.hpp"
#include <string>

class groupbox : public widget {
public:
  std::string_view resource_class() const override;
  virtual void output(YGNodeConstRef node, std::ostream& os) const override;
  void process_xaml(const pugi::xml_node& xaml, YGNodeRef node) override;
  void finalise_layout(YGNodeRef node) override;

private:
  std::string header_;
};
