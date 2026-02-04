#pragma once

#include <string>
#include <ostream>
#include <yoga/Yoga.h>
#include <pugixml.hpp>

class control {
public:
  virtual void output(YGNodeConstRef node, std::ostream& os) const = 0;
  virtual void from_xaml(const pugi::xml_node& xaml, YGNodeRef node) = 0;

  std::string id;

protected:
  std::string position_string(YGNodeConstRef node) const;
};
