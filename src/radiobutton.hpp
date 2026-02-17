#pragma once

#include "textwidget.hpp"

class radiobutton : public text_widget {
public:
  radiobutton(YGNodeRef node);

  std::string_view resource_class() const override;
};
