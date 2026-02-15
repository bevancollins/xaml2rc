#pragma once

#include <string>
#include "outputformat.hpp"

class playground_output : public output_format {
public:
  void output(YGNodeRef root, std::ostream& out) override;

private:
  void print_node(YGNodeRef node, std::ostream& out, int indent_level);
  std::string value_to_string(const YGValue& value);
};
