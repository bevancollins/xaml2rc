#pragma once

#include <ostream>
#include <yoga/Yoga.h>

class output_format {
public:
  output_format() = default;
  virtual ~output_format() = default;

  virtual void output(YGNodeRef root, std::ostream& out) = 0;
};
