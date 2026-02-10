#include "ltext.hpp"

std::string_view ltext::resource_class() const {
  return "LTEXT";
}

int ltext::default_height_dlu() const {
  return 8;
}
