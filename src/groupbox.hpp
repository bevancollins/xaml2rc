#pragma once

#include "widget.hpp"
#include <string>

class groupbox : public widget {
public:
  groupbox(YGNodeRef node);

  std::string_view resource_class() const override;
  virtual void output(std::ostream& os) const override;
  void process_xaml(const pugi::xml_node& xaml) override;

private:
  std::string header_;
};
