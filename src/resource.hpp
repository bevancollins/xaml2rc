#pragma once

#include <array>
#include <ostream>
#include <string_view>
#include <string>
#include <vector>
#include <yoga/Yoga.h>
#include <pugixml.hpp>

class resource {
public:
  virtual std::string_view resource_class() const = 0;
  virtual void output(YGNodeConstRef node, std::ostream& os) const = 0;
  virtual void from_xaml(const pugi::xml_node& xaml, YGNodeRef node);

protected:
  std::string x(YGNodeConstRef node) const;
  std::string y(YGNodeConstRef node) const;
  std::string width(YGNodeConstRef node) const;
  std::string height(YGNodeConstRef node) const;
  std::string style() const;
  std::string extended_style() const;
  std::string join_strings(const std::vector<std::string>& strings) const;
  std::array<int, 4> parse_quad(std::string_view input);

  std::string id_;
  std::vector<std::string> style_;
  std::vector<std::string> extended_style_;
};
