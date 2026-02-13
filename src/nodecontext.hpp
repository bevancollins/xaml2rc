#pragma once

#include <array>
#include <ostream>
#include <yoga/Yoga.h>
#include <pugixml.hpp>

class nodecontext {
public:
  nodecontext(YGNodeRef node);
  virtual ~nodecontext() = default;

  virtual void output(std::ostream& os) const;
  virtual void process_xaml(const pugi::xml_node& xaml);

protected:
  static void output_children(YGNodeRef node, std::ostream& os);

  std::array<int, 4> parse_quad(std::string_view input);
  YGJustify parse_justify(std::string_view alignment) const;
  YGAlign parse_align(std::string_view alignment) const;

  YGNodeRef node_{};
};
