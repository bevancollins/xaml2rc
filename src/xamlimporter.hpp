#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include <pugixml.hpp>
#include "resource.hpp"

class xamlimporter {
public:
  std::tuple<YGNodeRef, std::vector<std::unique_ptr<resource>>> import(const std::filesystem::path& path);

private:
  bool process_xaml(const pugi::xml_node& xaml, YGNodeRef node, std::vector<std::unique_ptr<resource>>& resources);
  void finalise_layout(YGNodeRef node);
};
