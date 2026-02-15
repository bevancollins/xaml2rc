#pragma once

#include "outputformat.hpp"

class resource_script_output : public output_format {
public:
  void output(YGNodeRef root, std::ostream& out) override;
};
