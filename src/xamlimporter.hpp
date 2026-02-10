#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <vector>
#include <pugixml.hpp>
#include "resource.hpp"

class xamlimporter {
public:
  std::tuple<YGNodeRef, std::vector<std::unique_ptr<resource>>> import(const std::filesystem::path& path);

private:
  YGNodeRef process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<resource>>& resources);
  void finalise_layout(YGNodeRef node);
};
