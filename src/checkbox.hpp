#pragma once

#include "textwidget.hpp"

class checkbox : public text_widget {
public:
  checkbox(YGNodeRef node);

  std::string_view resource_class() const override;
};
