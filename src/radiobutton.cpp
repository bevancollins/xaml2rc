#include "radiobutton.hpp"

std::string_view radiobutton::resource_class() const {
  return "RADIOBUTTON";
}

int radiobutton::default_height_dlu() const {
  return 10;
}
