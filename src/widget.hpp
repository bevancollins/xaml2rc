#pragma once

#include "resource.hpp"

class widget : public resource {
public:
  using resource::resource;

  void process_xaml(const pugi::xml_node& xaml) override;

  virtual int default_height_dlu() const;
};
