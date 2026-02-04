#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>
#include <pugixml.hpp>
#include "control.hpp"

class xamlimporter {
public:
  std::tuple<YGNodeRef, std::vector<std::unique_ptr<control>>> import(const std::filesystem::path& path);

private:
  YGNodeRef parse_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<control>>& controls);

  template<typename T>
  YGNodeRef parse_control(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<control>>& controls) {
    auto node = YGNodeNew();
    if (parent) {
      auto child_index = YGNodeGetChildCount(parent.value());
      YGNodeInsertChild(parent.value(), node, child_index);
    }

    auto control = std::make_unique<T>();
    YGNodeSetContext(node, control.get());

    control->from_xaml(xaml, node);

    controls.push_back(std::move(control));

    return node;
  }
};
