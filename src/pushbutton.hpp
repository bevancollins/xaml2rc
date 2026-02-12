#pragma once

#include "textwidget.hpp"

class pushbutton : public text_widget {
public:
  using text_widget::text_widget;

  std::string_view resource_class() const override;
  void process_xaml(const pugi::xml_node& xaml) override;
};
