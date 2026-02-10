#include "checkbox.hpp"

std::string_view checkbox::resource_class() const {
  return "CHECKBOX";
}

int checkbox::default_height_dlu() const {
  return 10;
}
