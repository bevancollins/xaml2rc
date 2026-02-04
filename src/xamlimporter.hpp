#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>
#include <pugixml.hpp>
#include "resource.hpp"

class xamlimporter {
public:
  std::tuple<YGNodeRef, std::vector<std::unique_ptr<resource>>> import(const std::filesystem::path& path);

private:
  YGNodeRef parse_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<resource>>& resources);

  template<typename T>
  YGNodeRef parse_resource(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<resource>>& resources) {
    auto node = YGNodeNew();
    if (parent) {
      auto child_index = YGNodeGetChildCount(parent.value());
      YGNodeInsertChild(parent.value(), node, child_index);
    }

    auto resource = std::make_unique<T>();
    YGNodeSetContext(node, resource.get());

    resource->from_xaml(xaml, node);

    resources.push_back(std::move(resource));

    return node;
  }
};
