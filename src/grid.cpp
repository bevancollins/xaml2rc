#include "grid.hpp"
#include <cassert>
#include <string_view>
#include <vector>
#include <iostream>

void grid::process_xaml(const pugi::xml_node& xaml) {
  nodecontext::process_xaml(xaml);

  std::vector<grid_length> row_lengths;
  std::vector<grid_length> column_lengths;

  for (auto const& row_definitions : xaml.children("Grid.RowDefinitions"))
    for (auto const& row_definition : row_definitions.children("RowDefinition")) {
      auto height_attr = row_definition.attribute("Height");
      if (height_attr)
        row_lengths.push_back(parse_length(height_attr.as_string()));
      else
        row_lengths.push_back({});
    }

  for (auto const& column_definitions : xaml.children("Grid.ColumnDefinitions"))
    for (auto const& column_definition : column_definitions.children("ColumnDefinition")) {
      auto width_attr = column_definition.attribute("Width");
      if (width_attr)
        column_lengths.push_back(parse_length(width_attr.as_string()));
      else
        column_lengths.push_back({});
    }

  rows_ = row_lengths.size();
  columns_ = column_lengths.size();

  // ensure at least 1 row and 1 column
  if (!rows_) rows_ = 1;
  if (!columns_) columns_ = 1;

  if (row_lengths.size() > column_lengths.size())
    YGNodeStyleSetFlexDirection(node_, YGFlexDirectionColumn);
  else
    YGNodeStyleSetFlexDirection(node_, YGFlexDirectionRow);

//  YGNodeStyleSetFlexGrow(node_, 1.0f);

  for (size_t row = 0; row < rows_; row++) {
    for (size_t column = 0; column < columns_; column++) {
      auto cell_node = YGNodeNew();
      auto cell_index = row + column * rows_;
      YGNodeInsertChild(node_, cell_node, cell_index);

      if (row < row_lengths.size()) {
        const auto& row_def = row_lengths[row];
        switch (row_def.type) {
          case grid_unit_type::Pixel:
            YGNodeStyleSetHeight(cell_node, row_def.value);
            break;
          case grid_unit_type::Auto:
            YGNodeStyleSetHeightAuto(cell_node);
            break;
          case grid_unit_type::Star:
            YGNodeStyleSetFlexGrow(cell_node, row_def.value);
            YGNodeStyleSetFlexDirection(cell_node, YGFlexDirectionColumn);
            break;
        }
      }

      if (column < column_lengths.size()) {
        const auto& col_def = column_lengths[column];
        switch (col_def.type) {
          case grid_unit_type::Pixel:
            YGNodeStyleSetWidth(cell_node, col_def.value);
            break;
          case grid_unit_type::Auto:
            YGNodeStyleSetWidthAuto(cell_node);
            break;
          case grid_unit_type::Star:
            YGNodeStyleSetFlexGrow(cell_node, col_def.value);
            YGNodeStyleSetFlexDirection(cell_node, YGFlexDirectionRow);
            break;
        }
      }
    }
  }
}

YGNodeRef grid::get_cell(size_t row, size_t column) {
  assert(row <= rows_);
  assert(column <= columns_);

  return YGNodeGetChild(node_, row + column * rows_);
}

grid::grid_length grid::parse_length(std::string_view value) const {
  if (value == "Auto") {
    return { grid_unit_type::Auto, 0.0f };
  } else if (value.ends_with('*')) {
    value.remove_suffix(1);
    float star_value{1.0f};
    if (!value.empty())
      std::from_chars(value.data(), value.data() + value.size(), star_value);

    return { grid_unit_type::Star, star_value };
  } else {
    float pixel_value{0.0f};
    std::from_chars(value.data(), value.data() + value.size(), pixel_value);
    return { grid_unit_type::Pixel, pixel_value };
  }
}
