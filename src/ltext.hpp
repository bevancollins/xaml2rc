#pragma once

#include "textwidget.hpp"

class ltext : public text_widget {
public:
  ltext(YGNodeRef node);

  std::string_view resource_class() const override;
};
