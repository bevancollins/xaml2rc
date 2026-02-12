#pragma once

#include "nodecontext.hpp"

class stackpanel : public nodecontext {
public:
  using nodecontext::nodecontext;

  void process_xaml(const pugi::xml_node& xaml) override;
};
