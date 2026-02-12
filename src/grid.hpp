#pragma once

#include <string_view>

#include "nodecontext.hpp"

class grid : public nodecontext {
public:
  using nodecontext::nodecontext;

  virtual void process_xaml(const pugi::xml_node& xaml);

  YGNodeRef get_cell(size_t row, size_t column);

private:
  enum class grid_unit_type {
    Auto,
    Pixel,
    Star
  };

  struct grid_length {
    grid_unit_type type{grid_unit_type::Star};
    float value{1.0f};
  };

  grid_length parse_length(std::string_view value) const;

  size_t rows_{};
  size_t columns_{};
};
